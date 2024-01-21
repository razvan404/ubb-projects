#include "pch.h"
#include "ConcursServer.hpp"

#define DEFAULT_BUFLEN  512
#define SERVER_PORT     "5678"

ConcursServer::ConcursServer(
    _In_    int                                 ClientProducersCount,
    _In_    int                                 ServerProducersCount,
    _Inout_ ProducerConsumerQueue<Participant>& PcQueue,
    _Inout_ RankingManager&                     RankingManager
) : pcQueue{ PcQueue }, rankingManager{ RankingManager }
{
    this->threadPool = std::make_unique<BS::thread_pool>(ServerProducersCount);
    this->clientProducersCount = ClientProducersCount;

    WSADATA wsaData = { 0 };
    int status = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (status)
    {
        const std::string& message = "WSAStartup failed with status " + std::to_string(status);
        throw std::exception(message.c_str());
    }
}

ConcursServer::~ConcursServer()
{
    int status = closesocket(this->listenSocket);
    if (status == SOCKET_ERROR)
    {
        const std::string& message = "closesocket failed with status " + std::to_string(WSAGetLastError());
        std::cout << message.c_str() << std::endl;
    }

    status = WSACleanup();
    if (status)
    {
        const std::string& message = "WSACleanup failed with status " + std::to_string(WSAGetLastError());
        std::cout << message.c_str() << std::endl;
    }
}

VOID
ConcursServer::Start()
{
    ADDRINFOA hints = { 0 };
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    PADDRINFOA result = nullptr;
    int status = getaddrinfo(NULL, SERVER_PORT, &hints, &result);
    if (status)
    {
        std::cout << "getaddrinfo failed with status " << status << std::endl;
        return;
    }

    this->listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (this->listenSocket == INVALID_SOCKET)
    {
        std::cout << "socket failed with status " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        return;
    }

    status = bind(this->listenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (status == SOCKET_ERROR)
    {
        std::cout << "bind failed with status " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        return;
    }

    freeaddrinfo(result);

    status = listen(this->listenSocket, SOMAXCONN);
    if (status == SOCKET_ERROR)
    {
        std::cout << "listen failed with status " << WSAGetLastError() << std::endl;
        return;
    }

    std::cout << "Server is ready and listening on port " << SERVER_PORT << std::endl;

    this->HandleConnections();
}

VOID
ConcursServer::HandleConnections()
{
    int connections = 0;
    while (connections < this->clientProducersCount)
    {
        SOCKADDR_IN clientInfo = { 0 };
        int clientInfoSize = sizeof(clientInfo);
        SOCKET* clientSocket = new SOCKET(accept(this->listenSocket, reinterpret_cast<PSOCKADDR>(&clientInfo), &clientInfoSize));
        if (*clientSocket == INVALID_SOCKET)
        {
            std::cout << "accept failed with status " << WSAGetLastError() << std::endl;
            closesocket(*clientSocket);
            delete clientSocket;
        }
        else
        {
            ++connections;
            this->threadPool->detach_task([&, clientSocket, clientInfo]
            {
                CHAR clientIP[INET_ADDRSTRLEN] = { 0 };
                inet_ntop(AF_INET, &clientInfo.sin_addr, clientIP, INET_ADDRSTRLEN);

                std::cout << "Client connected from IP: " << clientIP << std::endl;

                PCLIENT_CONTEXT clientContext = new CLIENT_CONTEXT{ .Socket = *clientSocket, .IPv4 = clientInfo.sin_addr };
                this->InsertNewClient(clientSocket, clientContext);
                this->HandleConnection(*clientContext);
            });
        }
    }
}

VOID
ConcursServer::HandleConnection(_Inout_ CLIENT_CONTEXT& ClientContext)
{
    int status = 0;
    do
    {
        CHAR buffer[DEFAULT_BUFLEN] = { 0 };
        int bufferSize = sizeof(buffer);

        status = recv(ClientContext.Socket, buffer, bufferSize, 0);
        if (status > 0)
        {
            std::string data(buffer, status);
            this->incompleteDataMap[ClientContext.Socket] += data;

#ifdef V2
            if (this->incompleteDataMap[ClientContext.Socket].ends_with("99999\r\n"))
            {
                this->ProcessData(this->incompleteDataMap[ClientContext.Socket], ClientContext);
                this->incompleteDataMap[ClientContext.Socket].erase();
                this->pcQueue.UnregisterProducer();
                ClientContext.NotSendingAnymore = true;
            }
            else if (this->incompleteDataMap[ClientContext.Socket].ends_with("99998\r\n"))
            {
                this->ProcessData(this->incompleteDataMap[ClientContext.Socket], ClientContext);
                std::thread([&]()
                {
                    std::promise<std::vector<std::pair<int, int>>> promise;
                    std::future<std::vector<std::pair<int, int>>> futureRanking = promise.get_future();

                    this->GetRankingManager().AddTask(promise);

                    const std::vector<std::pair<int, int>>& countryRanking = futureRanking.get();
                    this->Send(ClientContext.Socket, countryRanking);
                }).detach();
                this->incompleteDataMap[ClientContext.Socket].erase();
            }
#else
            size_t newlinePos;
            while ((newlinePos = this->incompleteDataMap[ClientContext.Socket].find("\r\n")) != std::string::npos)
            {
                std::string completeData = this->incompleteDataMap[ClientContext.Socket].substr(0, newlinePos + 2);
                this->ProcessData(completeData, ClientContext);

                this->incompleteDataMap[ClientContext.Socket].erase(0, newlinePos + 2);
            }
#endif
        }
        else if (!status)
        {
            std::cout << "Connection closing..." << std::endl;
            this->incompleteDataMap.erase(ClientContext.Socket);
        }
        else
        {
            std::cout << "recv failed: " << WSAGetLastError() << std::endl;
            this->incompleteDataMap.erase(ClientContext.Socket);
            return;
        }
    } while (status > 0 && !ClientContext.NotSendingAnymore);
}

VOID
ConcursServer::ProcessData(_In_ const std::string& Data, _Inout_ CLIENT_CONTEXT& ClientContext)
{
    if (!Data.ends_with("\r\n"))
    {
        return;
    }

#ifdef V2
    std::stringstream ss(Data);
    std::string token;
    while (std::getline(ss, token, '\r'))
    {
        if (ss.peek() == '\n')
        {
            ss.ignore();
        }

        std::stringstream tokenStream(token);
        int field1 = -2, field2 = -2;
        tokenStream >> field1 >> field2;

        if (field1 != -2 && field2 == -2 && field1 < 6)
        {
            ClientContext.Country = field1;
        }
        else if (field1 != -2 && field2 != -2)
        {
            if (!ClientContext.Country)
            {
                std::cout << "Logical error: ClientContext.Country is null" << std::endl;
                __debugbreak();
            }

            Participant participant;
            participant.SetId(field1);
            participant.SetScore(field2);
            participant.SetCountry(ClientContext.Country);

            this->pcQueue.Produce(participant);
        }
    }
#else
    const std::string& processedData = Data.substr(0, Data.size() - 2);

    if (!Data.contains(" "))
    {
        int data = std::stoi(processedData);
        if (data == 99998) // partial leaderboard request
        {
            std::thread([&]()
            {
                std::promise<std::vector<std::pair<int, int>>> promise;
                std::future<std::vector<std::pair<int, int>>> futureRanking = promise.get_future();

                this->GetRankingManager().AddTask(promise);

                const std::vector<std::pair<int, int>>& countryRanking = futureRanking.get();
                this->Send(ClientContext.Socket, countryRanking);
            }).detach();
        }
        else if (data == 99999) // final leaderboard request
        {
            this->pcQueue.UnregisterProducer();
            ClientContext.NotSendingAnymore = true;
        }
        else
        {
            ClientContext.Country = data;
        }
    }
    else
    {
        if (!ClientContext.Country)
        {
            std::cout << "Logical error: ClientContext.Country is null" << std::endl;
            __debugbreak();
        }

        Participant participant = Participant::Deserialize(processedData);
        participant.SetCountry(ClientContext.Country);

        this->pcQueue.Produce(participant);
    }
#endif
}

VOID
ConcursServer::SendFinalResults(
    _In_ const std::vector<std::pair<int, int>>& CountryRanking,
    _In_ const std::vector<std::pair<int, int>>& UserRanking
)
{
    for (const std::pair<SOCKET*, PCLIENT_CONTEXT>& client : this->clients)
    {
        this->Send(*client.first, CountryRanking);
        this->Send(*client.first, UserRanking);

        closesocket(*client.first);
        delete client.second;
        delete client.first;
    }
}
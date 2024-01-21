#ifndef _CONCURS_SERVER_HPP_
#define _CONCURS_SERVER_HPP_

#include "Participant.hpp"
#include "SynchPrimitive.hpp"
#include "RankingManager.hpp"

typedef struct _CLIENT_CONTEXT
{
    SOCKET  Socket = { 0 };
    IN_ADDR IPv4 = { 0 };
    int     Country = 0;
    bool    NotSendingAnymore = false;
} CLIENT_CONTEXT, * PCLIENT_CONTEXT;

class ConcursServer
{
    SOCKET listenSocket = { 0 };
    std::map<SOCKET*, PCLIENT_CONTEXT> clients;
    std::map<SOCKET, std::string> incompleteDataMap;
    std::unique_ptr<BS::thread_pool> threadPool;
    ProducerConsumerQueue<Participant>& pcQueue;
    RankingManager& rankingManager;
    int clientProducersCount;

public:
    ConcursServer(
        _In_    int                                 ClientProducersCount,
        _In_    int                                 ServerProducersCount,
        _Inout_ ProducerConsumerQueue<Participant>& PcQueue,
        _Inout_ RankingManager&                     RankingManager
    );
    ~ConcursServer();

    ConcursServer(_In_ const ConcursServer& Other) = delete;
    ConcursServer& operator=(_In_ const ConcursServer& Other) = delete;

    ConcursServer(_Inout_ ConcursServer&& Other) = delete;
    ConcursServer& operator=(_In_ ConcursServer&& Other) = delete;

    VOID
    Start();

    RankingManager&
    GetRankingManager() const
    {
        return this->rankingManager;
    }

    VOID
    Send(
        _In_ const SOCKET&                           ClientSocket,
        _In_ const std::vector<std::pair<int, int>>& Data
    )
    {
        std::stringstream ss;
        size_t size = Data.size();
        ss.write(reinterpret_cast<LPCSTR>(&size), sizeof(size));

        for (const std::pair<int, int>& pair : Data)
        {
            ss.write(reinterpret_cast<LPCSTR>(&pair.first), sizeof(pair.first));
            ss.write(reinterpret_cast<LPCSTR>(&pair.second), sizeof(pair.second));
        }

        const std::string& serializedData = ss.str();
        int totalBytesSent = 0;
        int bytesLeft = static_cast<int>(serializedData.size());

        while (bytesLeft > 0)
        {
            int bytesSent = send(ClientSocket, serializedData.c_str() + totalBytesSent, bytesLeft, 0);
            if (bytesSent == SOCKET_ERROR)
            {
                std::cout << "send failed with status " << WSAGetLastError() << std::endl;
                break;
            }
            totalBytesSent += bytesSent;
            bytesLeft -= bytesSent;
        }
    }

    VOID
    SendFinalResults(
        _In_ const std::vector<std::pair<int, int>>& CountryRanking,
        _In_ const std::vector<std::pair<int, int>>& UserRanking
    );

    VOID
    InsertNewClient(_In_ SOCKET* ClientSocket, _In_ PCLIENT_CONTEXT Context)
    {
        this->clients.emplace(ClientSocket, Context);
    }

private:
    VOID
    HandleConnections();

    VOID
    HandleConnection(_Inout_ CLIENT_CONTEXT& ClientContext);

    VOID
    ProcessData(_In_ const std::string& Data, _Inout_ CLIENT_CONTEXT& ClientContext);
};

#endif//_CONCURS_SERVER_HPP_
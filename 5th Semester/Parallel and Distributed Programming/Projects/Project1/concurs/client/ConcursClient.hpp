#ifndef _CONCURS_CLIENT_HPP_
#define _CONCURS_CLIENT_HPP_

#define DEFAULT_BUFLEN  512

class ConcursClient
{
    SOCKET serverSocket = INVALID_SOCKET;

public:
    ConcursClient();
    ~ConcursClient();

    ConcursClient(_In_ const ConcursClient& Other) = delete;
    ConcursClient& operator=(_In_ const ConcursClient& Other) = delete;

    ConcursClient(_Inout_ ConcursClient&& Other) = delete;
    ConcursClient& operator=(_In_ ConcursClient&& Other) = delete;

    bool
    Connect();

    VOID
    Disconnect();

    VOID
    Send(_In_ int Data)
    {
        const std::string& serializedData = std::to_string(Data) + "\r\n";
        int totalBytesSent = 0;
        int bytesLeft = static_cast<int>(serializedData.size());

        while (bytesLeft > 0)
        {
            int bytesSent = send(this->serverSocket, serializedData.c_str() + totalBytesSent, bytesLeft, 0);
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
    Send(_In_ LPCSTR Data, _In_ int DataSize)
    {
        int totalBytesSent = 0;
        int bytesLeft = DataSize;

        while (bytesLeft > 0)
        {
            int bytesSent = send(this->serverSocket, Data, DataSize, 0);
            if (bytesSent == SOCKET_ERROR)
            {
                std::cout << "send failed with status " << WSAGetLastError() << std::endl;
                break;
            }
            totalBytesSent += bytesSent;
            bytesLeft -= bytesSent;
        }
    }

    template <class T>
    VOID
    Send(_In_ const T& Data)
    {
        const std::string& serializedData = Data.Serialize() + "\r\n";
        int totalBytesSent = 0;
        int bytesLeft = static_cast<int>(serializedData.size());

        while (bytesLeft > 0)
        {
            int bytesSent = send(this->serverSocket, serializedData.c_str() + totalBytesSent, bytesLeft, 0);
            if (bytesSent == SOCKET_ERROR)
            {
                std::cout << "send failed with status " << WSAGetLastError() << std::endl;
                break;
            }
            totalBytesSent += bytesSent;
            bytesLeft -= bytesSent;
        }
    }

    template <class T>
    VOID
    Send(_In_ const std::vector<T>& DataChunk)
    {
        for (const T& data : DataChunk)
        {
            this->Send(data);
        }
    }

    VOID
    Recv(_Out_ std::vector<std::pair<int, int>>& Data)
    {
        CHAR buffer[DEFAULT_BUFLEN] = { 0 };
        int bytesReceived = recv(this->serverSocket, buffer, sizeof(size_t), 0);
        if (bytesReceived <= 0)
        {
            std::cout << "recv failed with status " << WSAGetLastError() << std::endl;
            return;
        }

        size_t size;
        memcpy_s(&size, sizeof(size), buffer, sizeof(size_t));

        std::string receivedData;
        int bytesToReceive = static_cast<int>(size) * (sizeof(int) * 2);
        int totalBytesReceived = 0;

        while (totalBytesReceived < bytesToReceive)
        {
            int bytesReceived = recv(serverSocket, buffer, min(DEFAULT_BUFLEN, bytesToReceive - totalBytesReceived), 0);
            if (bytesReceived <= 0)
            {
                std::cout << "recv failed with status " << WSAGetLastError() << std::endl;
                return;
            }
            receivedData.append(buffer, bytesReceived);
            totalBytesReceived += bytesReceived;
        }

        std::stringstream ss(receivedData);
        for (size_t i = 0; i < size; ++i)
        {
            int key = 0, value = 0;
            ss.read(reinterpret_cast<LPSTR>(&key), sizeof(key));
            ss.read(reinterpret_cast<LPSTR>(&value), sizeof(value));
            Data.emplace_back(key, value);
        }
    }
};

#endif//_CONCURS_CLIENT_HPP_
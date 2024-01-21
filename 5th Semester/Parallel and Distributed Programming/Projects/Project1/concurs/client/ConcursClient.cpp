#include "pch.h"
#include "ConcursClient.hpp"

#define SERVER_IP      "127.0.0.1"
#define SERVER_PORT    "5678"

ConcursClient::ConcursClient()
{
    WSADATA wsaData = { 0 };
    int status = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (status)
    {
        const std::string& message = "WSAStartup failed with status " + std::to_string(status);
        throw std::exception(message.c_str());
    }
}

ConcursClient::~ConcursClient()
{
    int status = WSACleanup();
    if (status)
    {
        const std::string& message = "WSACleanup failed with status " + std::to_string(WSAGetLastError());
        std::cout << message.c_str() << std::endl;
    }
}

bool
ConcursClient::Connect()
{
    ADDRINFOA hints = { 0 };
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    PADDRINFOA result = nullptr;
    int status = getaddrinfo(SERVER_IP, SERVER_PORT, &hints, &result);
    if (status)
    {
        std::cout << "getaddrinfo failed with status " << status << std::endl;
        return false;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    this->serverSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (this->serverSocket == INVALID_SOCKET)
    {
        std::cout << "socket failed with status " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        return false;
    }

    status = connect(this->serverSocket, result->ai_addr, (int)result->ai_addrlen);
    if (status == SOCKET_ERROR)
    {
        std::cout << "connect failed with status " << WSAGetLastError() << std::endl;
        closesocket(this->serverSocket);
        this->serverSocket = INVALID_SOCKET;
    }

    freeaddrinfo(result);

    return this->serverSocket != INVALID_SOCKET;
}

VOID
ConcursClient::Disconnect()
{
    if (this->serverSocket && this->serverSocket != INVALID_SOCKET)
    {
        closesocket(this->serverSocket);
    }
}
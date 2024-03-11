// MIT License
//
// Copyright (c) 2024 r0neko
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "tcp_server.hpp"


#include <fcntl.h>
#include <cstdio>
#include <memory>

#ifdef _WIN32

#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define MSG_DONTWAIT 0
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#endif

namespace core {
    TCPServer::TCPServer() : server_socket(-1) {
        WSADATA wsaData;

        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            printf("WSAStartup error!\n");
        }
    }

    TCPServer::~TCPServer() {
        stop();
        WSACleanup();
    }

    bool TCPServer::start(int port) {
        server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (server_socket == INVALID_SOCKET) {
            printf("Error creating socket.\n");
            return false;
        }

        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        serverAddr.sin_port = htons(port);

        if (bind(server_socket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
            printf("Bind failed.\n");
            closesocket(server_socket);
            return false;
        }

        if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {
            printf("Listen failed.\n");
            closesocket(server_socket);
            return false;
        }

        return true;
    }

    void TCPServer::stop() {
        for (auto& client : clients) {
            if (client->is_connected()) {
                client->close();
            }
        }

        clients.clear();

        if (server_socket != INVALID_SOCKET) {
            closesocket(server_socket);
            server_socket = INVALID_SOCKET;
        }
    }

    std::shared_ptr<TCPConnection> TCPServer::accept_connection() {
        sockaddr_in clientAddr{};
        int clientAddrLen = sizeof(clientAddr);

        auto clientSocket = accept(server_socket, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrLen);

        if (clientSocket == INVALID_SOCKET) {
            printf("accept failed!\n");
            return nullptr;
        }

        auto connection = std::make_shared<TCPConnection>(clientSocket);
        clients.push_back(connection);

        return connection;
    }

    bool TCPServer::has_new_connection() {
        fd_set readSet{};

        FD_ZERO(&readSet);
        FD_SET(server_socket, &readSet);

        timeval timeout = {0, 0};

        auto result = select(server_socket + 1, &readSet, nullptr, nullptr, &timeout);
        return (result > 0) && FD_ISSET(server_socket, &readSet);
    }
}
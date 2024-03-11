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

#ifndef TCP_SERVER_GUARD
#define TCP_SERVER_GUARD

#include "tcp_connection.hpp"

#include <memory>

#ifdef _WIN32

#include <winsock2.h>
#include <ws2def.h>

#else

#include <netinet/in.h>

#endif

namespace core {
    struct TCPServer {
        TCPServer();

        ~TCPServer();

        bool start(int port);

        void stop();

        std::shared_ptr<TCPConnection> accept_connection();

        bool has_new_connection();

    protected:
        int server_socket;
        sockaddr_in server_addr{};
        std::vector<std::shared_ptr<TCPConnection>> clients;
    };
}

#endif //TCP_SERVER_GUARD

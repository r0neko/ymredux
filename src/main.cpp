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

#include <core/tcp_server.hpp>

int main() {
    printf("YMRedux Server\n");

    core::TCPServer server;

    if(!server.start(5050)) {
        printf("Failed to start server!\n");
        return -1;
    }

    printf("Server started!\n");

    while (true) {
        if(server.has_new_connection()) {
            auto conn = server.accept_connection();

            if (conn) {
                printf("new connection from %s!\n", conn->get_ip().data());

                while(conn->is_connected()) {
                    std::vector<uint8_t> data = conn->read(sizeof(ymsg::YMSGHeader));

                    if (!data.empty()) {
                        printf("len %i\n", data.size());

                        for(auto c: data) {
                            printf("%02X ", c);
                        }
                        printf("\n");

                        auto header = ymsg::YMSGHeader{data.data()};
                        header.print_info();

//                        conn->send(data);
                    }
                }

                printf("lost connection\n");
            }
        }
    }

    server.stop();
    printf("Server stopped!\n");

    return 0;
}

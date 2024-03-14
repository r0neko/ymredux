// MIT License
//
// Copyright (c) 2024 r0neko, pushfq
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

#include <cstdlib>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <net/socket.h>
#include <net/packet.h>
#include <net/protocol/ymsg/ymsg_header.h>
#include <net/protocol/ymsg/ymsg_field.h>

void init_loggers() {
    spdlog::stdout_color_mt("system");
    spdlog::stdout_color_mt("net");
}

int32_t main() {
    init_loggers();
    net::impl::impl_init();

    spdlog::get("system")->info("Welcome to the YMRedux Server!");
    spdlog::get("system")->info("Initializing YMSG Server...");

    net::socket ymsg_sock(net::socket::type::stream);
    if(!ymsg_sock.bind(net::endpoint("127.0.0.1", 5050))) {
        spdlog::get("system")->error("Failed to bind!");
        return EXIT_FAILURE;
    }

    if (!ymsg_sock.listen()) {
        spdlog::get("system")->error("Failed to listen for connections!");
        return EXIT_FAILURE;
    }

    spdlog::get("system")->info("YMSG Server is listening for connections!");

    while (1) {
        auto client = ymsg_sock.accept();

        if (!client.has_value()) {
            continue;
        }

        auto &[socket, _] = client.value();

        spdlog::get("net")->info("New connection received!");

        net::serializer p_data;
        net::protocol::ymsg_field field(net::protocol::YMSG_FLD_CURRENT_ID, "cox");
        p_data.emplace<net::protocol::ymsg_field>(field);

        net::serializer s;
        s.emplace<net::protocol::ymsg_header>(16,
                                              0,
                                              p_data.size(),
                                              net::protocol::YES_USER_LOGIN,
                                              net::protocol::YES_STATUS_NOTIFY,
                                              0);
        s.serialize(p_data.data().data(), p_data.size());

        socket.write(s);
    }

    net::impl::impl_cleanup();
    return EXIT_SUCCESS;
}

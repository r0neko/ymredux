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

#include <server/server.h>
#include <server/handlers.h>

#include <spdlog/spdlog.h>

using namespace net::protocol;

// i ain't pasting this stuff 10001 times for each and every handler ~ r0neko, 14/03/2024
#define DEFINE_YMSG_HANDLER(op_code, handler) \
    case op_code: \
        handler(sock, header, fields); \
        break;

namespace server {
    void handle_frame(net::socket &sock, const ymsg_header &header,
                      const std::vector<ymsg_field> &fields) {
        spdlog::get("server")->debug("Handling frame type {0}, status {1:X}", (int) header.type, (int) header.status);

        for (const auto &field: fields) {
            spdlog::get("server")->debug("{0} = {1}", (int) field.key, field.value.data());
        }

        switch(header.type) {
            DEFINE_YMSG_HANDLER(YES_SEND_PORT_CHECK, handlers::handle_port_check)
            DEFINE_YMSG_HANDLER(YES_HELO, handlers::handle_helo)
            DEFINE_YMSG_HANDLER(YES_USER_LOGIN_2, handlers::handle_login_stage2)
            default:
                spdlog::get("server")->error("No case associated for this type!");
                break;
        }
    }
}

#undef DEFINE_YMSG_HANDLER

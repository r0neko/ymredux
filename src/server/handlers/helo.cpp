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

#include <server/handlers.h>

#include <spdlog/spdlog.h>

namespace server {
    namespace handlers {
        void handle_helo(net::socket &sock, const net::protocol::ymsg_header &header,
                         const std::vector<net::protocol::ymsg_field> &fields) {
            spdlog::get("server")->debug("Received HELO!");

            std::string username;

            for(const auto& field : fields) {
                if(field.key == YMSG_FLD_CURRENT_ID) {
                    username = field.value;
                    break;
                }
            }

            net::serializer response_fields;
            response_fields.emplace<net::protocol::ymsg_field>(YMSG_FLD_CURRENT_ID, username);
            response_fields.emplace<net::protocol::ymsg_field>(YMSG_FLD_FLAG, "2");
            response_fields.emplace<net::protocol::ymsg_field>(YMSG_FLD_CHALLENGE, "CHALLENGE-123");

            // ToDo: make YMSGClient class to handle proper sending
            net::serializer response;
            response.emplace<net::protocol::ymsg_header>(16,
                                                  0,
                                                  response_fields.size(),
                                                  YES_HELO,
                                                  YES_STATUS_NOTIFY,
                                                  0);
            response.serialize(response_fields.data().data(), response_fields.size());

            sock.write(response);
        }
    }
}
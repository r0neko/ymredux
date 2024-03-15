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
        void handle_login_stage2(net::socket &sock, const net::protocol::ymsg_header &header,
                                 const std::vector<net::protocol::ymsg_field> &fields) {
            std::string username{};
            std::string cookie_y{};
            std::string cookie_t{};
            std::string crumb_hash{};
            std::string client_country_code{"unknown"};
            std::string client_version{"unknown"};

            for (const auto &field: fields) {
                if (field.key == YMSG_FLD_CURRENT_ID) {
                    username = field.value;
                } else if (field.key == YMSG_FLD_LOGIN_Y_COOKIE) {
                    cookie_y = field.value;
                } else if (field.key == YMSG_FLD_LOGIN_T_COOKIE) {
                    cookie_t = field.value;
                } else if (field.key == YMSG_FLD_CRUMB_HASH) {
                    crumb_hash = field.value;
                } else if (field.key == YMSG_FLD_COUNTRY_CODE) {
                    client_country_code = field.value;
                } else if (field.key == YMSG_FLD_VERSION) {
                    client_version = field.value;
                }
            }

            spdlog::get("server")->debug("{0} is connecting from Y!M {1} ({2})", username.data(),
                                         client_version.data(), client_country_code.data());

            net::serializer response_fields;
            response_fields.emplace<net::protocol::ymsg_field>(YMSG_FLD_ERROR_CODE, "3");

            // ToDo: fail login
            net::serializer response;
            response.emplace<net::protocol::ymsg_header>(16,
                                                         0,
                                                         response_fields.size(),
                                                         YES_USER_LOGIN_2,
                                                         YES_STATUS_ERR,
                                                         0);
            response.serialize(response_fields.data().data(), response_fields.size());

            sock.write(response);
        }
    }
}
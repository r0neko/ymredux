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

#pragma once

#include <cstdint>

#include <net/packet.h>
#include <net/utility.h>

#include <net/protocol/ymsg/structure/ymsg_frame_field.h>

#include <spdlog/spdlog.h>

namespace net {
    namespace protocol {
        struct ymsg_field : protocol::ymsg_frame_field {
            using protocol::ymsg_frame_field::ymsg_frame_field;

            /**
             * @brief Serialize the message header.
             * @note To satisfy serializable.
             * @param s The serializer.
             */
            void serialize(serializer &s) const {
                auto key = std::to_string(this->key);

                s.serialize(key.data(), key.size());
                s.serialize(YMSG_FIELD_SEPARATOR);
                s.serialize(value.data(), value.size());
                s.serialize(YMSG_FIELD_SEPARATOR);

                spdlog::get("net")->debug("Serialize:");
                print_info();
            }

            /**
             * @brief Deserialize the message header.
             * @note To satisfy serializable.
             * @param d The deserializer.
             * @return true if the message header was successfully deserialized, false otherwise.
             */
            bool deserialize(deserializer &d) {
                auto key_size = d.find_pattern_first(YMSG_FIELD_SEPARATOR);

                if(key_size == -1) {
                    spdlog::get("net")->critical("field deserialize error; no key found in field!");
                    return false;
                }

                // read key as string
                std::string key_str{};
                key_str.reserve(key_size);

                d.deserialize(key_str.data(), key_size);
                d.deserialize_ignore(2); // ignore separator

                auto value_size = d.find_pattern_first(YMSG_FIELD_SEPARATOR);

                if(value_size == -1) {
                    spdlog::get("net")->critical("field deserialize error; no value found in field!");
                    return false;
                }

                value.reserve(value_size);

                d.deserialize(value.data(), value_size);
                d.deserialize_ignore(2); // ignore separator

                spdlog::get("net")->debug("Deserialize:");
                print_info();

                return true;
            }

            void print_info() const {
                spdlog::get("net")->debug("YMSGField (");
                spdlog::get("net")->debug("    key = {0}", (int) key);
                spdlog::get("net")->debug("    value = {0}", value);
                spdlog::get("net")->debug(")");
            }
        };
    }  // namespace protocol
}  // namespace net

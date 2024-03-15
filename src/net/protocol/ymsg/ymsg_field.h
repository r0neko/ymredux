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
             * @brief Construct and deserialize the field.
             * @param d The deserializer.
             */
            explicit ymsg_field(deserializer &d) {
                deserialize(d);
            }

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

                printf("Serialize:\n");
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
                key_str.resize(key_size);

                d.deserialize(key_str.data(), key_size);
                d.deserialize_ignore(2); // ignore separator

                key = (YMSG_FLD_) std::stoi(key_str);

                auto value_size = d.find_pattern_first(YMSG_FIELD_SEPARATOR);

                if(value_size == -1) {
                    spdlog::get("net")->critical("field deserialize error; no value found in field!");
                    return false;
                }

                value.resize(value_size);

                d.deserialize(value.data(), value_size);
                d.deserialize_ignore(2); // ignore separator

                printf("Deserialize:\n");
                print_info();

                return true;
            }

            void print_info() const {
                printf("YMSGField (\n");
                printf("    key = %i\n", (int) key);
                printf("    value = %s\n", value.data());
                printf(")\n");
            }
        };
    }  // namespace protocol
}  // namespace net

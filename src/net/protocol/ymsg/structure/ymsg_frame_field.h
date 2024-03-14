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
#include <string>
#include <string_view>

#include <net/protocol/ymsg/enums/ymsg_field_type.hpp>

namespace net {
    namespace protocol {
        constexpr auto YMSG_FIELD_SEPARATOR = static_cast<std::uint16_t>(0xC080);

        struct [[gnu::packed]] ymsg_frame_field {
            /**
             * @brief Constructor.
             * @param protocol_version The protocol version.
             * @param value The field value
             */
            explicit constexpr ymsg_frame_field(
                    YMSG_FLD_ key, std::string_view value)
                    : key(key),
                      value(value) {}

            YMSG_FLD_ key;
            std::string value;
        };
    }  // namespace protocol
}  // namespace net
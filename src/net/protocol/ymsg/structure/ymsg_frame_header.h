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

#include <net/protocol/ymsg/enums/ymsg_message_type.hpp>
#include <net/protocol/ymsg/enums/ymsg_status_type.hpp>

namespace net {
    namespace protocol {
        constexpr auto YMSG_HEADER_MAGIC = static_cast<std::uint32_t>(0x47534D59);

        struct [[gnu::packed]] ymsg_frame_header {
            /**
             * @brief Constructor.
             * @param protocol_version The protocol version.
             * @param vendor_id The vendor ID.
             * @param length The length of the message.
             * @param type The type of the message.
             * @param status The status of the message.
             * @param session_id The session ID.
             */
            explicit constexpr ymsg_frame_header(
                    std::uint16_t protocol_version, std::uint16_t vendor_id, std::uint16_t length,
                    YES_ type, YES_STATUS_ status, std::uint32_t session_id)
                    : magic(YMSG_HEADER_MAGIC),
                      protocol_version(protocol_version),
                      vendor_id(vendor_id),
                      length(length),
                      type(type),
                      status(status),
                      session_id(session_id) {}

            constexpr ymsg_frame_header() = default;

            std::uint32_t magic;
            std::uint16_t protocol_version;
            std::uint16_t vendor_id;
            std::uint16_t length;
            YES_ type;
            YES_STATUS_ status;
            std::uint32_t session_id;
        };
    }  // namespace protocol
}  // namespace net
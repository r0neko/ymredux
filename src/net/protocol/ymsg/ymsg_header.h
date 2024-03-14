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

#include <net/protocol/ymsg/structure/ymsg_frame_header.h>

#include <spdlog/spdlog.h>

namespace net {
    namespace protocol {
        // deserialize with endian conversion macro
#define DESERIALIZE_CVT(d, x) \
  do {                     \
    if (!d.deserialize(x)) \
      return false;        \
    (x) = cvt_endian(x);   \
  } while (0)

        struct ymsg_header : protocol::ymsg_frame_header {
            using protocol::ymsg_frame_header::ymsg_frame_header;

            /**
             * @brief Serialize the message header.
             * @note To satisfy serializable.
             * @param s The serializer.
             */
            void serialize(serializer &s) const {
                s.serialize(YMSG_HEADER_MAGIC);
                s.serialize(cvt_endian(protocol_version));
                s.serialize(cvt_endian(vendor_id));
                s.serialize(cvt_endian(length));
                s.serialize(cvt_endian((std::uint16_t) type));
                s.serialize(cvt_endian((std::uint32_t) status));
                s.serialize(cvt_endian(session_id));

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
                if (!d.deserialize(magic)) {
                    return false;
                }

                if (magic != YMSG_HEADER_MAGIC) {
                    return false;
                }

                DESERIALIZE_CVT(d, protocol_version);
                DESERIALIZE_CVT(d, vendor_id);
                DESERIALIZE_CVT(d, length);

                if (!d.deserialize((std::uint16_t&) type)) {
                    return false;
                }

                type = (YES_) cvt_endian((std::uint16_t) type);

                if (!d.deserialize((std::int32_t&) status)) {
                    return false;
                }

                status = (YES_STATUS_) cvt_endian((std::int32_t) status);

                DESERIALIZE_CVT(d, session_id);

                spdlog::get("net")->debug("Deserialize:");
                print_info();

                return true;
            }

            void print_info() const {
                spdlog::get("net")->debug("YMSGHeader (");
                spdlog::get("net")->debug("    magic = 0x{0:X}", magic);
                spdlog::get("net")->debug("    protocol_version = {0}", protocol_version);
                spdlog::get("net")->debug("    vendor_id = {0:X}", vendor_id);
                spdlog::get("net")->debug("    length = {0}", length);
                spdlog::get("net")->debug("    type = {0:X}", (uint16_t) type);
                spdlog::get("net")->debug("    status = {0:X}", (uint32_t) status);
                spdlog::get("net")->debug("    session_id = {0:X}", session_id);
                spdlog::get("net")->debug(")\n");
            }
        };

#undef DESERIALIZE_CVT
    }  // namespace protocol
}  // namespace net

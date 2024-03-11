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

#ifndef YMSG_HEADER_GUARD
#define YMSG_HEADER_GUARD

#include <cstdint>
#include <vector>

#include <core/utils/endian.hpp>

namespace ymsg {
    constexpr uint32_t YMSG_HEADER_MAGIC = 0x47534D59;

#pragma pack(push, 1)

    struct YMSGHeader {
        uint32_t magic;
        uint16_t protocol_version;
        uint16_t vendor_id;
        uint16_t length;
        uint16_t type;
        uint32_t status;
        uint32_t session_id;

        explicit YMSGHeader(unsigned char *data) {
            auto v = (YMSGHeader *) data;

            magic = v->magic;
            protocol_version = v->protocol_version;
            vendor_id = v->vendor_id;
            length = v->length;
            type = v->type;
            status = v->status;
            session_id = v->session_id;

            // fix endianness
            protocol_version = core::utils::to_big_endian(protocol_version);
            vendor_id = core::utils::to_big_endian(vendor_id);
            length = core::utils::to_big_endian(length);
            type = core::utils::to_big_endian(type);
            status = core::utils::to_big_endian(status);
            session_id = core::utils::to_big_endian(session_id);
        }

        void print_info() {
            printf("YMSGHeader (\n");
            printf("    magic = 0x%X\n", magic);
            printf("    protocol_version = %x\n", protocol_version);
            printf("    vendor_id = %X\n", vendor_id);
            printf("    length = %i\n", length);
            printf("    type = %X\n", type);
            printf("    status = %X\n", status);
            printf("    session_id = %X\n", session_id);
            printf(")\n");
        }
    };

#pragma pack(pop, 1)
}

#endif //YMSG_HEADER_GUARD

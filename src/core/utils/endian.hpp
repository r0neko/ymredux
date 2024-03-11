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

#ifndef ENDIAN_GUARD
#define ENDIAN_GUARD

namespace core {
    namespace utils {
        uint16_t to_big_endian(uint16_t value) {
            return (value >> 8) | (value << 8);
        }

        uint32_t to_big_endian(uint32_t value) {
            return ((value >> 24) & 0xFF) |
                   ((value >> 8) & 0xFF00) |
                   ((value << 8) & 0xFF0000) |
                   ((value << 24) & 0xFF000000);
        }

        uint64_t to_big_endian(uint64_t value) {
            return ((value >> 56) & 0xFF) |
                   ((value >> 40) & 0xFF00) |
                   ((value >> 24) & 0xFF0000) |
                   ((value >> 8) & 0xFF000000) |
                   ((value << 8) & 0xFF00000000) |
                   ((value << 24) & 0xFF0000000000) |
                   ((value << 40) & 0xFF000000000000) |
                   ((value << 56) & 0xFF00000000000000);
        }
    }
}

#endif //ENDIAN_GUARD

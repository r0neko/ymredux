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

#include <type_traits>

namespace net {

/**
 * @brief Convert the endianness of a value.
 * @pre The type of the value must be an integral type. Additionally, its size must be 2, 4, or 8.
 * @tparam T The type of the value.
 * @param value The value to convert.
 * @return The value with the endianness flipped.
 */
    template<typename T>
    requires std::is_integral_v<T>
    constexpr T cvt_endian(T value) {
        static_assert(sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8);

        if constexpr (sizeof(T) == 2)
            return _byteswap_ushort(value);

        if constexpr (sizeof(T) == 4)
            return _byteswap_ulong(value);

        if constexpr (sizeof(T) == 8)
            return _byteswap_uint64(value);
    }

}  // namespace net

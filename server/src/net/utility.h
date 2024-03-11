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
template <typename T>
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

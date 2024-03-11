
#pragma once

#include <cstdint>

#include "packet.h"
#include "utility.h"

namespace net {

struct [[gnu::packed]] raw_message_header {
  /**
   * @brief Constructor.
   * @param magic The magic number.
   * @param protocol_version The protocol version.
   * @param vendor_id The vendor ID.
   * @param length The length of the message.
   * @param type The type of the message.
   * @param status The status of the message.
   * @param session_id The session ID.
   */
  explicit constexpr raw_message_header(
    std::uint32_t magic, std::uint32_t protocol_version, std::uint32_t vendor_id, std::uint32_t length,
    std::uint32_t type, std::uint32_t status, std::uint32_t session_id)
    : magic(magic),
      protocol_version(protocol_version),
      vendor_id(vendor_id),
      length(length),
      type(type),
      status(status),
      session_id(session_id) {}

  std::uint32_t magic;
  std::uint32_t protocol_version;
  std::uint32_t vendor_id;
  std::uint32_t length;
  std::uint32_t type;
  std::uint32_t status;
  std::uint32_t session_id;
};

#define DESERIALIZE_CVT(x) \
  do {                     \
    if (!d.deserialize(x)) \
      return false;        \
    (x) = cvt_endian(x);   \
  } while (0)

struct message_header : raw_message_header {
  using raw_message_header::raw_message_header;

  /**
   * @brief Serialize the message header.
   * @note To satisfy serializable.
   * @param s The serializer.
   */
  void serialize(serializer& s) const {
    s.serialize(magic);
    s.serialize(cvt_endian(protocol_version));
    s.serialize(cvt_endian(vendor_id));
    s.serialize(cvt_endian(length));
    s.serialize(cvt_endian(type));
    s.serialize(cvt_endian(status));
    s.serialize(cvt_endian(session_id));
  }

  /**
   * @brief Deserialize the message header.
   * @note To satisfy serializable.
   * @param d The deserializer.
   * @return true if the message header was successfully deserialized, false otherwise.
   */
  bool deserialize(deserializer& d) {
    if (!d.deserialize(magic))
      return false;

    DESERIALIZE_CVT(protocol_version);
    DESERIALIZE_CVT(vendor_id);
    DESERIALIZE_CVT(length);
    DESERIALIZE_CVT(type);
    DESERIALIZE_CVT(status);
    DESERIALIZE_CVT(session_id);

    return magic == static_cast<std::uint32_t>('GSMY');
  }
};

#undef DESERIALIZE_CVT

}  // namespace net

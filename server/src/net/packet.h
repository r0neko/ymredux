#pragma once

#include <algorithm>
#include <iterator>
#include <span>
#include <vector>

namespace net {

template <typename T>
concept serializable = requires(const T& p1, T& p2) {
  { p1.serialize(std::declval<struct serializer&>()) };
  { p2.deserialize(std::declval<struct deserializer&>()) } -> std::same_as<bool>;
};

struct serializer {
  using value_type = std::byte;
  using iterator = std::vector<value_type>::iterator;
  using const_iterator = std::vector<value_type>::const_iterator;

  /**
   * @brief Begin iterator.
   * @return An iterator to the beginning of the serialized data.
   */
  iterator begin() {
    return buffer_.begin();
  }

  /**
   * @brief Begin iterator.
   * @return An iterator to the beginning of the serialized data.
   */
  const_iterator begin() const {
    return buffer_.begin();
  }

  /**
   * @brief End iterator.
   * @return An iterator to the end of the serialized data.
   */
  iterator end() {
    return buffer_.end();
  }

  /**
   * @brief End iterator.
   * @return An iterator to the end of the serialized data.
   */
  const_iterator end() const {
    return buffer_.end();
  }

  /**
   * @brief Serialize data.
   * @param data Input buffer.
   * @param len Length of the input buffer.
   */
  void serialize(const void* data, std::size_t len) {
    buffer_.reserve(buffer_.size() + len);
    std::copy_n(static_cast<const std::byte*>(data), len, std::back_inserter(buffer_));
  }

  /**
   * @brief Serialize data.
   * @param value The value to serialize.
   * @tparam T The type of the value. Must satisfy trivially_copyable and must not satisfy serializable.
   */
  template <typename T>
    requires(std::is_trivially_copyable_v<T> && !serializable<T>)
  void serialize(const T& value) {
    serialize(&value, sizeof(value));
  }

  /**
   * @brief Serialize data.
   * @param value The value to serialize.
   * @tparam T The type of the value. Must satisfy serializable.
   */
  template <serializable T>
  void serialize(const T& value) {
    value.serialize(*this);
  }

  /**
   * @brief Construct and serialize an object.
   * @tparam T The type of the object. Must satisfy serializable.
   * @tparam As The types of the arguments to forward to the constructor of T.
   * @param args The arguments to forward to the constructor of T.
   */
  template <serializable T, typename... As>
  void emplace(As&&... args) {
    T(std::forward<As>(args)...).serialize(*this);
  }

  /**
   * @brief Get the serialized data.
   * @return The serialized data.
   */
  std::span<const std::byte> data() const {
    return buffer_;
  }

 private:
  std::vector<std::byte> buffer_;
};

struct deserializer {
  /**
   * @brief Constructor.
   * @param data The data to dissect and deserialize.
   */
  explicit deserializer(std::span<const std::byte> data) : data_(data) {}

  /**
   * @brief Deserialize data.
   * @param data Output buffer.
   * @param len Length of the output buffer.
   * @return true if the data was deserialized, false otherwise.
   */
  bool deserialize(void* data, size_t len) {
    if (data_.size() < len)
      return false;

    std::memcpy(data, data_.data(), len);
    data_ = data_.subspan(len);

    return true;
  }

  /**
   * @brief Deserialize data.
   * @param value The value to deserialize.
   * @tparam T The type of the value. Must satisfy trivially_copyable and must not satisfy serializable.
   * @return true if the data was deserialized, false otherwise.
   */
  template <typename T>
    requires(std::is_trivially_copyable_v<T> && !serializable<T>)
  bool deserialize(T& value) {
    return deserialize(&value, sizeof(value));
  }

  /**
   * @brief Deserialize data.
   * @param value The value to deserialize.
   * @tparam T The type of the value. Must satisfy serializable.
   * @return true if the data was deserialized, false otherwise.
   */
  template <serializable T>
  bool deserialize(T& value) {
    return value.deserialize(*this);
  }

 private:
  std::span<const std::byte> data_;
};

}  // namespace net

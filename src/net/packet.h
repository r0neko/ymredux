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

#include <algorithm>
#include <iterator>
#include <span>
#include <vector>

namespace net {
//    // MSVC doesn't like our concepts, so we'll just get rid of them... for now.
//    template<typename T>
//    concept serializable = requires(const T &p) {
//        { p.serialize(std::declval<struct serializer &>()) };
//    };
//
//    template<typename T>
//    concept deserializable = requires(T &p) {
//        { p.deserialize(std::declval<struct deserializer &>()) } -> std::same_as<bool>;
//    };

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
        void serialize(const void *data, std::size_t len) {
            buffer_.reserve(buffer_.size() + len);
            std::copy_n(static_cast<const std::byte *>(data), len, std::back_inserter(buffer_));
        }

        /**
         * @brief Serialize data.
         * @param value The value to serialize.
         * @tparam T The type of the value. Must satisfy trivially_copyable and must not satisfy serializable.
         */
        template<typename T>
//        requires(std::is_trivially_copyable_v<T> && !serializable<T>)
        requires(std::is_trivially_copyable_v<T>)
        void serialize(const T &value) {
            serialize(&value, sizeof(value));
        }

        /**
         * @brief Serialize data.
         * @param value The value to serialize.
         * @tparam T The type of the value. Must satisfy serializable.
         */
//        template<serializable T>
        template<typename T>
        void serialize(const T &value) {
            value.serialize(*this);
        }

        /**
         * @brief Construct and serialize an object.
         * @tparam T The type of the object. Must satisfy serializable.
         * @tparam As The types of the arguments to forward to the constructor of T.
         * @param args The arguments to forward to the constructor of T.
         */
//        template<serializable T, typename... As>
        template<typename T, typename... As>
        void emplace(As &&... args) {
            T(std::forward<As>(args)...).serialize(*this);
        }

        /**
         * @brief Get the serialized data.
         * @return The serialized data.
         */
        std::span<const std::byte> data() const {
            return buffer_;
        }

        /**
        * @brief Get the length of the serialized data.
        * @return The length of the serialized data.
        */
        size_t size() const {
            return buffer_.size();
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
        bool deserialize(void *data, size_t len) {
            if (data_.size() < len)
                return false;

            std::memcpy(data, data_.data(), len);
            data_ = data_.subspan(len);

            return true;
        }

        bool deserialize_ignore(size_t len) {
            if (data_.size() < len)
                return false;

            data_ = data_.subspan(len);

            return true;
        }

        /**
         * @brief Finds the first occurrence of a value in the data.
         * @tparam T The type of the value.
         * @return offset if the pattern value was found, -1 otherwise.
         */
        template<typename T>
        size_t find_pattern_first(T &value) {
            if (data_.size() < sizeof(value))
                return static_cast<size_t>(-1);

            for(size_t i = 0; i < data_.size() - sizeof(value); i++) {
                if(std::memcmp(data_.data() + i, &value, sizeof(value)) == 0) {
                    return i;
                }
            }

            return static_cast<size_t>(-1);
        }

        /**
         * @brief Deserialize data.
         * @param value The value to deserialize.
         * @tparam T The type of the value. Must satisfy trivially_copyable and must not satisfy deserializable.
         * @return true if the data was deserialized, false otherwise.
         */
        template<typename T>
//        requires(std::is_trivially_copyable_v<T> && !deserializable<T>)
        requires(std::is_trivially_copyable_v<T>)
        bool deserialize(T &value) {
            return deserialize(&value, sizeof(value));
        }

        /**
         * @brief Deserialize data.
         * @param value The value to deserialize.
         * @tparam T The type of the value. Must satisfy deserializable.
         * @return true if the data was deserialized, false otherwise.
         */
//        template<deserializable T>
        template<typename T>
        bool deserialize(T &value) {
            return value.deserialize(*this);
        }

    private:
        std::span<const std::byte> data_;
    };

}  // namespace net

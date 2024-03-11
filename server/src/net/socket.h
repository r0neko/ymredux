#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>

#include <array>
#include <iterator>
#include <optional>
#include <string_view>
#include <utility>

namespace net {

namespace impl {

[[gnu::constructor]] inline void wsa_init() {
  WSADATA wsa_data;
  WSAStartup(MAKEWORD(2, 2), &wsa_data);
}

[[gnu::destructor]] inline void wsa_cleanup() {
  WSACleanup();
}

}  // namespace impl

template <typename T>
concept socket_buffer = std::ranges::range<T> && std::is_trivially_copyable_v<typename T::value_type> &&
                        std::is_convertible_v<typename T::value_type, std::byte>;

struct endpoint {
  /**
   * @brief Constructor.
   * @param address The address of the endpoint.
   * @param port The port of the endpoint.
   */
  explicit constexpr endpoint(std::string_view address, std::uint16_t port) {
    address_.sin_family = AF_INET;
    address_.sin_port = htons(port);

    inet_pton(AF_INET, address.data(), &address_.sin_addr);
  }

  /**
   * @brief Constructor.
   * @param address The address of the endpoint.
   */
  explicit constexpr endpoint(sockaddr_in address) : address_(address) {}

  /**
   * @brief Gets the underlying sockaddr_in.
   * @return The underlying sockaddr_in.
   */
  constexpr sockaddr_in get() const {
    return address_;
  }

 private:
  sockaddr_in address_;
};

struct socket {
  using socket_type = SOCKET;

  enum type {
    stream = 1,
    dgram = 2,
    raw = 3,
    rdm = 4,
    seqpacket = 5,
  };

  constexpr static socket_type invalid_socket = static_cast<socket_type>(-1);

  /**
   * @brief Constructor.
   * @param socket The socket to wrap.
   */
  explicit constexpr socket(socket_type socket) : socket_(socket) {}

  /**
   * @brief Constructor.
   * @param type The type of the socket.
   */
  explicit constexpr socket(type type) {
    socket_ = ::socket(AF_INET, std::to_underlying(type), 0);
  }

  /**
   * @brief Default constructor.
   * @note Initializes an invalid socket.
   */
  constexpr socket() : socket_(invalid_socket) {}

  /**
   * @brief Move constructor.
   * @param other The socket to move from.
   */
  constexpr socket(socket&& other) noexcept : socket_(std::exchange(other.socket_, invalid_socket)) {}

  /**
   * @brief Destructor.
   * @note Closes the socket.
   */
  ~socket() {
    close();
  }

  /**
   * @brief Move assignment operator.
   * @param other The socket to move from.
   * @return A reference to this socket.
   */
  constexpr socket& operator=(socket&& other) noexcept {
    if (this != std::addressof(other)) {
      close();
      socket_ = std::exchange(other.socket_, invalid_socket);
    }

    return *this;
  }

  socket(const socket& other) = delete;
  socket& operator=(const socket& other) = delete;

  /**
   * @brief Tests if the socket is valid.
   * @return true if the socket is valid, false otherwise.
   */
  constexpr bool is_valid() const {
    return socket_ != invalid_socket;
  }

  /**
   * @brief Gets the underlying socket.
   * @return The underlying socket.
   */
  constexpr socket_type get() const {
    return socket_;
  }

  /**
   * @brief Closes the socket.
   */
  void close() {
    if (socket_ != invalid_socket) {
      closesocket(socket_);
      socket_ = invalid_socket;
    }
  }

  /**
   * @brief Read from the socket.
   * @param buffer The buffer to read into.
   * @param length The length of the buffer.
   * @return The number of bytes read, or -1 on error.
   */
  std::int32_t read_some(void* buffer, std::size_t length) {  // NOLINT(readability-make-member-function-const)
    return recv(socket_, static_cast<char*>(buffer), static_cast<int>(length), 0);
  }

  /**
   * @brief Write to the socket.
   * @param buffer The buffer to write from.
   * @param length The length of the buffer.
   * @return The number of bytes written, or -1 on error.
   */
  std::int32_t write_some(const void* buffer, std::size_t length) {  // NOLINT(readability-make-member-function-const)
    return send(socket_, static_cast<const char*>(buffer), static_cast<int>(length), 0);
  }

  /**
   * @brief Read from the socket.
   * @param container The container to read into.
   * @tparam T The type of the container. Must satisfy socket_buffer.
   * @return true if the read was successful, false otherwise.
   */
  template <socket_buffer T>
  bool read(T& container) {  // NOLINT(readability-make-member-function-const)
    std::array<std::byte, BUFSIZ> buffer{};

    do {
      const auto bytes_read = read_some(buffer.data(), buffer.size());
      if (bytes_read <= 0) {
        return false;
      }

      container.reserve(container.size() + bytes_read);

      std::copy_n(buffer.begin(), bytes_read, std::back_inserter(container));
    } while (container.size() < container.max_size());

    return true;
  }

  /**
   * @brief Write to the socket.
   * @param container The container to write from.
   * @tparam T The type of the container. Must satisfy socket_buffer.
   * @return true if the write was successful, false otherwise.
   */
  template <socket_buffer T>
  bool write(const T& container) {  // NOLINT(readability-make-member-function-const)
    for (auto it = container.begin(); it != container.end();) {
      const auto bytes_written = write_some(std::addressof(*it), std::distance(it, container.end()));
      if (bytes_written <= 0) {
        return false;
      }

      std::advance(it, bytes_written);
    }

    return true;
  }

  /**
   * @brief Listen for incoming connections.
   * @param backlog The maximum length of the queue of pending connections.
   * @return true if the listen was successful, false otherwise.
   */
  bool listen(std::int32_t backlog = SOMAXCONN) {  // NOLINT(readability-make-member-function-const)
    return ::listen(socket_, backlog) == 0;
  }

  /**
   * @brief Accept an incoming connection.
   * @return The accepted socket and endpoint, or std::nullopt on error.
   */
  std::optional<std::pair<socket, endpoint>> accept() {  // NOLINT(readability-make-member-function-const)
    sockaddr_in address;
    socklen_t length = static_cast<socklen_t>(sizeof(address));

    const auto client_socket = ::accept(socket_, reinterpret_cast<sockaddr*>(&address), &length);
    if (client_socket == invalid_socket) {
      return std::nullopt;
    }

    return std::make_pair(socket(client_socket), endpoint(address));
  }

  /**
   * @brief Bind the socket to an endpoint.
   * @param endpoint The endpoint to bind to.
   * @return true if the bind was successful, false otherwise.
   */
  bool bind(const endpoint& endpoint) {  // NOLINT(readability-make-member-function-const)
    const auto& address = endpoint.get();
    return ::bind(socket_, reinterpret_cast<const sockaddr*>(&address), sizeof(address)) == 0;
  }

  /**
   * @brief Connect the socket to an endpoint.
   * @param endpoint The endpoint to connect to.
   * @return true if the connect was successful, false otherwise.
   */
  bool connect(const endpoint& endpoint) {  // NOLINT(readability-make-member-function-const)
    const auto& address = endpoint.get();
    return ::connect(socket_, reinterpret_cast<const sockaddr*>(&address), sizeof(address)) == 0;
  }

 private:
  socket_type socket_;
};

}  // namespace net

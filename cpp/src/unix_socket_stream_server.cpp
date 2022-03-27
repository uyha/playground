#include <array>
#include <fmt/core.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

int main() {
  constexpr auto path = "/tmp/sandbox/unix-socket";

  auto server_fd = ::socket(AF_UNIX, SOCK_DGRAM, 0);
  if (server_fd == -1) {
    fmt::print(::stderr, "Couldn't create a socket: {}\n", ::strerror(errno));
    return errno;
  }

  if (::remove(path) == -1 and errno != ENOENT) {
    fmt::print(::stderr, "Couldn't remove existing file: {}\n", ::strerror(errno));
    return errno;
  }

  auto server_addr = ::sockaddr_un{};
  ::memset(&server_addr, 0, sizeof(::sockaddr_un));
  server_addr.sun_family = AF_UNIX;
  strncpy(server_addr.sun_path, path, sizeof(server_addr.sun_path) - 1);

  if (::bind(server_fd, (::sockaddr *)&server_addr, sizeof(::sockaddr_un)) == -1) {
    fmt::print(::stderr, "Couldn't bind to address: {}\n", ::strerror(errno));
    return errno;
  }

  auto buffer        = std::array<char, 255>{};
  auto client_addr   = ::sockaddr_un{};
  auto client_length = ::socklen_t{sizeof(::sockaddr_un)};
  while (true) {
    auto num_bytes = ::recvfrom(server_fd,
                                std::data(buffer),
                                std::size(buffer),
                                0,
                                (::sockaddr *)&client_addr,
                                &client_length);

    if (num_bytes == -1) {
      fmt::print(::stderr, "Failed to receive from client: {}\n", ::strerror(errno));
      return errno;
    }

    fmt::print("Received {} bytes from {}\n", num_bytes, client_addr.sun_path);

    if (::sendto(
            server_fd, std::data(buffer), num_bytes, 0, (::sockaddr *)&client_addr, client_length)
        != num_bytes) {
      fmt::print(::stderr, "Failed to send to client: {}\n", ::strerror(errno));
      return errno;
    }
  }
}

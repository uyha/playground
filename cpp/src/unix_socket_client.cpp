#include <array>
#include <fmt/core.h>
#include <string.h>
#include <string_view>
#include <sys/socket.h>
#include <sys/un.h>
#include <linux/can/bcm.h>

int main(int argc, char **argv) {
  constexpr auto path = "/tmp/sandbox/unix-socket-client";

  auto client_fd = ::socket(AF_UNIX, SOCK_DGRAM, 0);
  if (client_fd == -1) {
    fmt::print(::stderr, "Couldn't create a socket: {}\n", ::strerror(errno));
    return errno;
  }
  auto client_addr = ::sockaddr_un{};
  ::memset(&client_addr, 0, sizeof(::sockaddr_un));
  client_addr.sun_family = AF_UNIX;
  strncpy(client_addr.sun_path, path, sizeof(client_addr.sun_path) - 1);

  if (::bind(client_fd, (::sockaddr *)&client_addr, sizeof(::sockaddr_un)) == -1) {
    fmt::print(::stderr, "Couldn't bind to address: {}\n", ::strerror(errno));
    return errno;
  }

  auto server_addr = ::sockaddr_un{};
  ::memset(&server_addr, 0, sizeof(::sockaddr_un));
  server_addr.sun_family = AF_UNIX;
  strncpy(server_addr.sun_path, "/tmp/sandbox/unix-socket", sizeof(server_addr.sun_path) - 1);

  auto buffer = std::array<char, 255>{};

  for (auto i = 1; i < argc; ++i) {
    ::ssize_t num_bytes = ::strlen(argv[i]);
    if (::sendto(
            client_fd, argv[i], num_bytes, 0, (::sockaddr *)&server_addr, sizeof(::sockaddr_un))
        != num_bytes) {
      fmt::print(::stderr, "Failed to send to server: {}\n", ::strerror(errno));
      return errno;
    }

    num_bytes = ::recvfrom(client_fd, std::data(buffer), std::size(buffer), 0, nullptr, nullptr);
    if (num_bytes == -1) {
      fmt::print(::stderr, "Failed to receive from server: {}\n", ::strerror(errno));
      return errno;
    }
    fmt::print("Received {} bytes from server: {}\n",
               num_bytes,
               std::string_view{std::data(buffer), std::size(buffer)});
  }

  /* ::remove(path); */
}

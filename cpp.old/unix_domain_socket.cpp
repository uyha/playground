#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

void listen() {
  constexpr auto socket_name = "/tmp/sandbox/listener";

  ::unlink(socket_name);

  auto sock = ::socket(AF_UNIX, SOCK_DGRAM, 0);
  if (sock == -1) {
    std::cerr << std::strerror(errno) << std::endl;
  }

  auto address = sockaddr_un{};
  std::memset(&address, 0, sizeof(sockaddr_un));

  address.sun_family = AF_UNIX;
  std::strncpy(address.sun_path, socket_name, sizeof(address.sun_path) - 1);

  if (auto const return_code =
          ::bind(sock, (sockaddr const *)&address, sizeof(sockaddr_un));
      return_code == -1) {
    std::cerr << std::strerror(errno) << std::endl;
  }

  if (auto const return_code = ::listen(sock, 20); return_code == -1) {
  }
}

int main() {}

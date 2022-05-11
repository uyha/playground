#include <cassert>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <fmt/format.h>
#include <sys/socket.h>
#include <sys/un.h>

int main() {
  constexpr auto name1 = "/tmp/socket-sandbox-1";
  constexpr auto name2 = "/tmp/socket-sandbox-2";

  auto socket = ::socket(AF_UNIX, SOCK_DGRAM, 0);
  assert(socket != -1);

  ::sockaddr_un addr = {};
  addr.sun_family    = AF_UNIX;
  std::memcpy(addr.sun_path, name1, std::strlen(name1));
  addr.sun_path[std::strlen(name1)] = '\0';

  fmt::print(
      "{}: {}\n", __LINE__, ::bind(socket, reinterpret_cast<::sockaddr *>(&addr), sizeof(addr)));
  fmt::print("{}: {}\n", __LINE__, errno);

  std::memcpy(addr.sun_path, name2, std::strlen(name2));
  fmt::print(
      "{}: {}\n", __LINE__, ::bind(socket, reinterpret_cast<::sockaddr *>(&addr), sizeof(addr)));
  fmt::print("{}: {}\n", __LINE__, errno);

  (void)EINVAL;
  (void)EADDRINUSE;
}

#include <cstring>
#include <fmt/printf.h>
#include <sys/socket.h>
#include <sys/un.h>

void server() {
  auto s = ::socket(AF_UNIX, SOCK_STREAM, 0);
  ::sockaddr_un addr{};
  addr.sun_family                   = AF_UNIX;
  [[maybe_unused]] socklen_t length = sizeof(addr);
  decltype(auto) path               = "/tmp/un";
  std::memcpy(addr.sun_path, path, std::size(path));
  fmt::print("{}\n", ::remove(path));
  fmt::print("{}\n", ::bind(s, reinterpret_cast<::sockaddr *>(&addr), sizeof(addr)));
  fmt::print("{}\n", ::listen(s, 2));
  fmt::print("{}\n", errno);
  while (true) {
    fmt::print("{}\n", ::accept(s, nullptr, nullptr));
  }
}

void client() {
  auto s = ::socket(AF_UNIX, SOCK_STREAM, 0);
  ::sockaddr_un addr{};
  addr.sun_family     = AF_UNIX;
  decltype(auto) path = "/tmp/un";
  std::memcpy(addr.sun_path, path, std::size(path));
  fmt::print("{}\n", ::connect(s, reinterpret_cast<::sockaddr *>(&addr), sizeof(addr)));
  fmt::print("{}\n", errno);
  while (true) {
  }
}

int main(int argc, char **argv) {
  using std::string_view_literals::operator""sv;

  if (argc < 2 or argv[1] == "server"sv) {
    server();
  } else {
    client();
  }
}

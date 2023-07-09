#include <fmt/printf.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  auto path = "/home/uy/sandbox/cpp/build/src/ctad";
  auto pid  = ::fork();
  fmt::print("pid: {}\n", pid);
  if (pid == 0) {
    auto error = ::execl(path, path, (char *)NULL);
    if (error) {
      fmt::print("{}\n", std::strerror(errno));
    }
  }
  fmt::print("pid: {}\n", pid);
}

#include <fmt/printf.h>
#include <zmq.hpp>

int main() {
  auto const [major, minor, patch] = zmq::version();
  fmt::print("{}.{}.{}\n", major, minor, patch);
}

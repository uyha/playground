#include <fmt/core.h>

template <std::size_t size>
auto print(char const (&str)[size]) -> void {
  fmt::print("{}\n", str);
  fmt::print("{}\n", size);
}

int main() {
  print("hello");
}

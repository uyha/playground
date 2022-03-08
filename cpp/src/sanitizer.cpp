#include <fmt/printf.h>
enum class A { a };

bool maybe(A b) {
  return b == A::a;
}

int main(int argc, [[maybe_unused]] char **argv) {
  fmt::print("{}\n", argc);

  auto a = static_cast<A>(argc - 1);

  return maybe(a) ? static_cast<int>(a) / (argc - 1) : 0;
}

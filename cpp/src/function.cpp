#include <fmt/core.h>
#include <functional>

struct A {
  auto operator()() & -> void {
    a++;
  }

  int a = 0;
};

int main() {
  auto a                   = A{};
  std::function<void()> fn = [&] { a(); };
  fn();
  fn();
  fn();
  fn();
  fmt::print("{}\n", a.a);
}

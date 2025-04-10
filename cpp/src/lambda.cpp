#include <fmt/core.h>
#include <type_traits>

class A {
public:
  struct B {
    auto call(A const &a) -> void {
      a.print();
    }
  };

private:
  auto print() const -> void {
    fmt::print("{}:{}\n", __FILE__, __LINE__);
    (void)::fflush(::stdout);
  }
};

int main() {
  auto lambda = [] {};
  static_assert(std::is_convertible_v<decltype(lambda), auto (*)()->void>);

  auto a = A{};
  auto b = A::B{};
  b.call(a);
}

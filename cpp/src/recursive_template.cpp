#include <type_traits>

template <typename S>
struct A {
  using B = S::B;
};

struct Spec {
  using A = ::A<Spec>;
  using B = float;
};

int main() {
  static_assert(std::is_same_v<Spec::A::B, float>);
  return 0;
}

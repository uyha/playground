#include <fmt/core.h>
#include <memory>
#include <river/fn.hpp>

struct A {
  A()                         = default;
  A(A &&)                     = delete;
  auto operator=(A &&) -> A & = delete;
  virtual auto act1() -> void = 0;

  virtual ~A() = default;
};

struct B : A {
  B(int a_)
      : a{a_} {}

  auto act1() -> void override {
    fmt::print("B: {{a: {}}}\n", a);
  }

  int a;
};

struct C : A {
  auto act1() -> void override {
    fmt::print("C\n");
  }
};

int main() {
  auto fun             = river::fn<&A::act1>{};
  std::unique_ptr<A> b = std::make_unique<B>(1);
  std::unique_ptr<A> c = std::make_unique<C>();
  A *ref               = b.get();

  fun(*ref);
  c = std::make_unique<B>(1);
  fun(*c);
}

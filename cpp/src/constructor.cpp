struct A {
  constexpr A() = default;

  A(A const &)                     = delete;
  auto operator=(A const &) -> A & = delete;

  A(A &&)                     = default;
  auto operator=(A &&) -> A & = default;
};

void fn(A) {}

int main() {
  auto a = A{};
  fn(static_cast<A &&>(a));
}

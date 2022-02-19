namespace sandbox {
enum class A : int {};
} // namespace sandbox
template <typename A> struct BitOr {
  friend constexpr auto operator|(A lhs, A rhs) -> A {
    return static_cast<A>(static_cast<int>(lhs) | static_cast<int>(rhs));
  }
};
template BitOr<sandbox::A>;

int main() {
  using namespace sandbox;
  static_cast<A>(1) | static_cast<A>(2);
}

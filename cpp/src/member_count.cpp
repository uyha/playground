#include <array>
#include <fmt/printf.h>
#include <string>
#include <type_traits>

struct UniversalType {
  template <typename T>
  operator T();
};

template <typename T, typename... Args>
consteval auto member_count() {
  static_assert(std::is_aggregate_v<std::remove_cvref_t<T>>);

  if constexpr (not requires { T{Args{}..., UniversalType{}}; }) {
    return sizeof...(Args);
  } else {
    return member_count<T, Args..., UniversalType>();
  }
}

struct A {};
struct B {
  int a;
  std::array<int, 2> b;
  std::string c;
};

static_assert(std::is_aggregate_v<B>);

template <typename T>
consteval auto fn() {
  if constexpr (not requires {
                      T{UniversalType{}, UniversalType{}, UniversalType{}, UniversalType{}};
                    }) {
    return 3;
  }
  return 0;
}

int main() {
  static_assert(member_count<A>() == 0);
  static_assert(member_count<B>() == 3);
  static_assert(fn<B>() == 3);
}

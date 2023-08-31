#include <type_traits>

int main() {
  auto lambda = [] {};
  static_assert(std::is_convertible_v<decltype(lambda), auto (*)()->void>);
}

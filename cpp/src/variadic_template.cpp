#include <cassert>
#include <fmt/format.h>
#include <optional>
#include <string_view>
#include <type_traits>
#include <variant>

using namespace std::string_view_literals;

auto read_fn(std::string const &s, std::type_identity_t<int>) -> std::optional<int> {
  if (s == "int"sv) {
    return 0;
  }
  return std::nullopt;
}

auto read_fn(std::string const &s, std::type_identity_t<float>) -> std::optional<float> {
  if (s == "float"sv) {
    return 0;
  }
  return std::nullopt;
}

template <typename T>
auto read_fn(std::string const &s) -> std::optional<T> {
  return read_fn(s, std::type_identity_t<T>{});
}

template <typename T1, typename T2, typename... Ts>
auto read_fn(std::string const &s) -> std::optional<std::variant<T1, T2, Ts...>> {
  auto result = read_fn(s, std::type_identity_t<T1>{});
  if (result) {
    return *result;
  }
  return read_fn<T2, Ts...>(s);
}

template <typename... Ts, typename... TTs>
auto var_fn(Ts..., bool = true, TTs...)
  requires((not std::is_same_v<Ts, bool>) && ...)
{
  fmt::print("{}\n", __PRETTY_FUNCTION__);
}

int main() {
  var_fn(1, 2, 3, 4.0);
}

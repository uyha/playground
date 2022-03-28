#include <fmt/format.h>
#include <fmt/ranges.h>
#include <iterator>
#include <netdb.h>

struct NullSentinel {
  template <typename T>
  friend auto operator==(T **const &lhs, NullSentinel const &) -> bool {
    return *lhs == nullptr;
  }
  template <typename T>
  friend auto operator==(NullSentinel const &, T **const &rhs) -> bool {
    return *rhs == nullptr;
  }
  template <typename T>
  friend auto operator!=(T **const &lhs, NullSentinel const &) -> bool {
    return *lhs != nullptr;
  }
  template <typename T>
  friend auto operator!=(NullSentinel const &, T **const &rhs) -> bool {
    return *rhs != nullptr;
  }
};

template <>
struct fmt::formatter<::protoent> {
  constexpr auto parse(format_parse_context &context) -> decltype(context.begin()) {
    return context.begin();
  }
  template <typename Context>
  auto format(::protoent const &value, Context &context) -> decltype(context.out()) {
    return format_to(context.out(),
                     "{{p_name = {}, p_aliases = {}, p_proto = {}}}",
                     value.p_name,
                     fmt::join(value.p_aliases, NullSentinel{}, ", "),
                     value.p_proto);
  }
};

int main() {
  ::setprotoent(true);

  while (true) {
    auto proto = getprotoent();
    if (not proto) {
      break;
    }
    fmt::print("{}\n", *proto);
  }
  ::endprotoent();
}

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <netdb.h>
#include <vector>

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
  constexpr auto parse(format_parse_context &context) -> format_parse_context::iterator {
    return context.begin();
  }
  auto format(::protoent const &value, format_context &context) const -> format_context::iterator {
    auto aliases = std::vector<std::string>{};
    for (auto begin = value.p_aliases; *begin != nullptr; ++begin) {
      aliases.push_back(*begin);
    }
    return format_to(context.out(),
                     "{{p_name = {}, p_aliases = {}, p_proto = {}}}",
                     value.p_name,
                     aliases,
                     value.p_proto);
  }
};

int main() {
  ::setprotoent(true);

  while (true) {
    auto *proto = getprotoent();
    if (not proto) {
      break;
    }
    fmt::print("{}\n", *proto);
  }
  ::endprotoent();
}

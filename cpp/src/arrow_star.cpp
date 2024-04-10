#include <fmt/core.h>
#include <optional>

template <typename Fn>
struct Expr {
  constexpr auto operator->*(auto &&expression) const {
    return fn(std::forward<decltype(expression)>(expression));
  }
  constexpr auto operator,(auto &&expression) const {
    return operator->*(std::forward<decltype(expression)>(expression));
  }

  Fn fn;
};

#define check                                                                                      \
  expr({                                                                                           \
    if (not expr) {                                                                                \
      std::exit(1); /* NOLINT(*mt-unsafe) */                                                       \
    }                                                                                              \
  }),

#define unwrap                                                                                     \
  Expr([](auto &&expression) {                                                                     \
    if constexpr (requires { expression.has_value(); }) {                                          \
      if (not expression.has_value()) {                                                            \
        throw std::bad_optional_access{};                                                          \
      }                                                                                            \
    }                                                                                              \
    return std::move(*expression);                                                                 \
  })->*

// struct Lifetime {
//   constexpr Lifetime() {
//     fmt::print("Default constructor\n");
//   }
//
//   constexpr Lifetime(Lifetime const &) {
//     fmt::print("Copy constructor\n");
//   }
//   constexpr auto operator=(Lifetime const &) -> Lifetime & {
//     fmt::print("Copy assignment\n");
//     return *this;
//   }
//
//   constexpr Lifetime(Lifetime &&) noexcept {
//     fmt::print("Move constructor\n");
//   }
//   constexpr auto operator=(Lifetime &&) -> Lifetime & {
//     fmt::print("Move assignment\n");
//     return *this;
//   }
//
//   constexpr ~Lifetime() noexcept {
//     fmt::print("Destructor\n");
//   }
// };

int main() {
  constexpr auto a = unwrap std::optional<int>{1};
  fmt::print("{}\n", "hello");
  (void)a;
}

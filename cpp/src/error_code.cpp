#include <fmt/core.h>
#include <system_error>

enum class MyError {
  first = 1,
  second,
  third,
  fourth,
};

namespace {
struct MyErrorCategory : std::error_category {
  auto name() const noexcept -> char const * override {
    return "My Error";
  }
  auto message(int condition) const -> std::string override {
    switch (static_cast<MyError>(condition)) {
    case MyError::first:
      return "First Error";
    default:
      return "Unknwon error";
    }
  }
};
const MyErrorCategory my_error_category{};
} // namespace

template <>
struct std::is_error_code_enum<MyError> : std::true_type {};
auto make_error_code(MyError error) -> std::error_code {
  return {static_cast<int>(error), my_error_category};
}

int main() {
  std::error_code err = MyError::first;
  fmt::print("{}\n", err.message());
}

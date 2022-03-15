#include <fmt/core.h>
#include <system_error>

namespace lpipp {
struct SomeStruct {
  enum class SomeEnum {};
  friend auto make_error_code(SomeEnum) -> std::error_code;
};
} // namespace lpipp

template <>
struct std::is_error_code_enum<lpipp::SomeStruct::SomeEnum> : std::true_type {};

namespace {
struct SomeEnumCategory : std::error_category {
  auto name() const noexcept -> char const * override {
    return "SomeEnumCategory";
  }
  auto message(int) const -> std::string override {
    return "Unknown error";
  }
};

SomeEnumCategory some_enum_category{};
} // namespace

namespace lpipp {
auto make_error_code(lpipp::SomeStruct::SomeEnum) -> std::error_code {
  return {static_cast<int>(1), some_enum_category};
}
} // namespace lpipp

int main() {
  std::error_code err = (lpipp::SomeStruct::SomeEnum)(1);
  fmt::print("{}\n", err.message());
}

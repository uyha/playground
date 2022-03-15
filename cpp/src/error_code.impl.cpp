#include <system_error>

namespace m_namespace {
enum class MyError {
  first = 1,
  second,
  third,
  fourth,
};
auto make_error_code(MyError error) -> std::error_code;
} // namespace m_namespace
namespace {
struct MyErrorCategory : std::error_category {
  auto name() const noexcept -> char const * override {
    return "My Error";
  }
  auto message(int condition) const -> std::string override {
    switch (static_cast<m_namespace::MyError>(condition)) {
    case m_namespace::MyError::first:
      return "First Error";
    default:
      return "Unknwon error";
    }
  }
};
const MyErrorCategory my_error_category{};
} // namespace

auto m_namespace::make_error_code(MyError error) -> std::error_code {
  return {static_cast<int>(error), my_error_category};
}

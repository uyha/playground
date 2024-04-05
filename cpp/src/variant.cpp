#include <fmt/core.h>
#include <variant>

int main() {
  auto value = std::variant<int, int, int>{std::in_place_index<2>, 1};
  fmt::print("{}\n", value.index());
}

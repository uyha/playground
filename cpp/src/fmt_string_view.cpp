#include <fmt/printf.h>
#include <string_view>

int main() {
  decltype(auto) message = "{:<2} world";
  fmt::print(std::string_view{message, std::size(message) - 5}, 1);
}

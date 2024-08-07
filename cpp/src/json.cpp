#include <fmt/core.h>
#include <nlohmann/json.hpp>

int main() {
  auto json = nlohmann::json{
      {"a", {"asd", "123"}},
      {"b", 1},
      {"c", 1},
      {"d", 1},
  };

  fmt::print("{}\n", json.dump());
}

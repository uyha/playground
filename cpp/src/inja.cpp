#include <fmt/core.h>
#include <inja/inja.hpp>

int main() {
  auto data    = nlohmann::json{};
  data["name"] = "asdf";

  fmt::print("{}",
             inja::render(R"jinja(
hello {{name}}
)jinja",
                          data));
  return 0;
}

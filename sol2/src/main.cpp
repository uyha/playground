#include <fmt/format.h>
#include <sol/sol.hpp>

int main(int, char **argv) {
  auto lua = sol::state{};

  lua.open_libraries(sol::lib::base);

  auto result = lua.script_file(argv[1]);
  fmt::print("{}:{} {}\n", __FILE__, __LINE__, (int)result.get<sol::table>()[1].get<sol::table>()["id"].get_type());
  (void)::fflush(::stdout);
  for (auto const &[key, value] : result.get<sol::table>()) {
    fmt::print("{}:{} {}\n", __FILE__, __LINE__, value.as<sol::table>().size());
    (void)::fflush(::stdout);
  }
}

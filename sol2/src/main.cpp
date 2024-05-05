#include <fmt/format.h>
#include <sol/sol.hpp>

struct Lifetime {
  Lifetime() {
    fmt::print("Default constructor\n");
  }

  Lifetime(Lifetime const &) {
    fmt::print("Copy constructor\n");
  }
  auto operator=(Lifetime const &) -> Lifetime & {
    fmt::print("Copy assignment\n");
    return *this;
  }

  Lifetime(Lifetime &&) noexcept {
    fmt::print("Move constructor\n");
  }
  auto operator=(Lifetime &&) -> Lifetime & {
    fmt::print("Move assignment\n");
    return *this;
  }

  ~Lifetime() noexcept {
    fmt::print("Destructor\n");
  }
};

int main(int, char **argv) {
  auto lua = sol::state{};

  lua.open_libraries(sol::lib::base);
  lua.new_usertype<Lifetime>("Lifetime");

  auto result = lua.script_file(argv[1]);
}

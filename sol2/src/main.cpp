#include <fmt/format.h>
#include <map>
#include <sol/sol.hpp>

struct FnMap {
public:
  auto get(std::string const &key) -> std::optional<sol::function> {
    auto it = m_functions.find(key);
    if (it != m_functions.end()) {
      return it->second;
    }
    return std::nullopt;
  }

  auto set(std::string const &key, sol::function fn) {
    m_functions[key] = fn;
  }

private:
  std::map<std::string, sol::function> m_functions;
};

struct Demo {
  int a;
};

int main(int, char **argv) {
  fmt::print("Hello, {}\n", "World");
  auto lua = sol::state{};

  lua.open_libraries(sol::lib::base);

  auto callbacks                           = lua.new_usertype<FnMap>("FnMap");
  callbacks[sol::meta_function::new_index] = &FnMap::set;
  callbacks[sol::meta_function::index]     = &FnMap::get;

  auto demo = lua.new_usertype<Demo>("Demo");
  demo["a"] = &Demo::a;

  auto d  = Demo{.a = 1};
  auto fn = lua.script_file(argv[1]).get<FnMap>();
  fn.get("print").value()(d);
  fn.get("print").value()(d);
  fn.get("print").value()(d);
  fn.get("print").value()(d);
  fn.get("print").value()(d);

  // if (a) {
  //   fmt::print("{}:{}\n", __FILE__, __LINE__);
  //   (void)::fflush(::stdout);
  //   a();
  //   fmt::print("{}:{}\n", __FILE__, __LINE__);
  //   (void)::fflush(::stdout);
  // }
}

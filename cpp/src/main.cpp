#include <fmt/core.h>
#include <mutex>

auto get_unique_inproc_endpoint(std::string_view prefix) -> std::string {
  static auto count = std::size_t{0};
  static auto mutex = std::mutex{};

  auto lock = std::scoped_lock{mutex};

  return fmt::format("inproc://{}-{}", prefix, count++);
}

int main() {
  fmt::print("{}\n", get_unique_inproc_endpoint("pre").c_str());
  fmt::print("{}\n", get_unique_inproc_endpoint("asdf"));

  return 0;
}

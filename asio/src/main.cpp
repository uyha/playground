#include <asio.hpp>
#include <chrono>
#include <fmt/format.h>

using namespace std::chrono_literals;

void print(asio::error_code const &, asio::steady_timer &timer, int &count) {
  if (count >= 5) {
    return;
  }

  fmt::print("{}\n", count++);

  timer.expires_from_now(1ms);
  timer.async_wait([&](auto const &error_code) { print(error_code, timer, count); });
}

int main() {
  auto context = asio::io_context{};
  auto count   = 0;

  auto timer = asio::steady_timer{context, 1ms};
  timer.async_wait([&](auto const &error_code) { print(error_code, timer, count); });

  context.run();

  fmt::print("Final count is {}\n", count);
}

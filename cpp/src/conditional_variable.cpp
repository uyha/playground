#include <chrono>
#include <condition_variable>
#include <fmt/chrono.h>
#include <fmt/format.h>
#include <mutex>
#include <thread>

int main() {
  using namespace std::chrono;
  using namespace std::chrono_literals;

  auto cond_var = std::condition_variable{};
  auto start    = steady_clock::now();
  auto mutex    = std::mutex();

  auto thread = std::jthread{[&cond_var, &mutex](std::stop_token token) {
    while (not token.stop_requested()) {
      auto lock = std::unique_lock{mutex};
      cond_var.wait_for(lock, 0.1s);
    }
  }};

  for (auto i = 0; i < 1'000'000; ++i) {
    cond_var.notify_one();
  }
  auto dur = (steady_clock::now() - start) / 1'000'000;
  fmt::print("{}\n", dur);
}

#include <chrono>
#include <fmt/chrono.h>
#include <fmt/printf.h>
#include <pthread.h>
#include <thread>

int main() {
  using namespace std::chrono_literals;
  ::pthread_rwlock_t lock;
  fmt::print("{}\n", ::pthread_rwlock_init(&lock, nullptr));

  constexpr auto loop = 1'000'000;

  auto const start = std::chrono::steady_clock::now();
  for (auto i = 0; i < loop; ++i) {
    ::pthread_rwlock_wrlock(&lock);
    ::pthread_rwlock_unlock(&lock);
  }
  auto const end = std::chrono::steady_clock::now();

  fmt::print("{}\n", ::pthread_rwlock_destroy(&lock));
  fmt::print("{}\n", (end - start) / loop);
}

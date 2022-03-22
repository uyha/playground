#include <chrono>
#include <fcntl.h>
#include <fmt/chrono.h>
#include <sys/file.h>
#include <sys/mman.h>

int main() {
  auto const shm_name = "/sandbox.flock.shm";

  auto shm = ::shm_open(shm_name, O_RDONLY | O_CREAT, 0666);
  fmt::print("shm: {}\n", shm);

  constexpr auto loop = 1'000'000;

  auto const start = std::chrono::steady_clock::now();

  for (auto i = 0; i < loop; ++i) {
    ::flock(shm, LOCK_SH);
    ::flock(shm, LOCK_UN);
  }

  auto const end = std::chrono::steady_clock::now();
  fmt::print("{}\n", (end - start) / loop);
}

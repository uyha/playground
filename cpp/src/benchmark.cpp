#include <chrono>
#include <fcntl.h>
#include <fmt/chrono.h>
#include <sys/file.h>
#include <sys/mman.h>

int main() {
  auto const shm_name = "/sandbox.flock.shm";
  volatile int a      = 1;

  auto shm = ::shm_open(shm_name, O_RDONLY | O_CREAT, 0666);
  fmt::print("shm: {}\n", shm);

  auto const start = std::chrono::steady_clock::now();

  for (auto i = 0; i < 1000; ++i) {
    ::flock(shm, LOCK_SH);
    a = a + 1;
    ::flock(shm, LOCK_UN);
  }

  auto const end = std::chrono::steady_clock::now();
  fmt::print("{}\n", end - start);
}

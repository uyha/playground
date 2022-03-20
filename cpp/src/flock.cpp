#include <atomic>
#include <csignal>
#include <fmt/core.h>
#include <sys/file.h>
#include <sys/mman.h>

std::atomic_bool should_stop = false;

int main() {
  std::signal(SIGINT, [](int) { should_stop = true; });

  auto const shm_name = "/sandbox.flock.shm";

  auto shm = ::shm_open(shm_name, O_RDONLY | O_CREAT, 0666);
  fmt::print("{}\n", shm);
  auto lock_result = ::flock(shm, LOCK_SH);
  fmt::print("{}\n", lock_result);

  if (lock_result) {
    fmt::print("{}\n", errno);
    return lock_result;
  }

  while (not should_stop)
    ;

  fmt::print("{}\n", ::flock(shm, LOCK_UN));
  fmt::print("{}\n", ::shm_unlink(shm_name));
  (void)EBADF;
}

#include <atomic>
#include <csignal>
#include <fmt/core.h>
#include <sys/epoll.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <unistd.h>

std::atomic_bool should_stop = false;

auto flock_epoll() {
  auto epoll = ::epoll_create1(0);
  fmt::print("epoll: {}\n", epoll);

  auto lock_result = ::flock(epoll, LOCK_EX);
  fmt::print("{}\n", lock_result);

  if (lock_result) {
    fmt::print("{}\n", errno);
  }
  return [epoll]() { fmt::print("{}\n", ::close(epoll)); };
}

auto flock_shm() {
  auto const shm_name = "/sandbox.flock.shm";

  auto shm = ::shm_open(shm_name, O_RDONLY | O_CREAT, 0666);
  fmt::print("shm: {}\n", shm);
  auto lock_result = ::flock(shm, LOCK_EX);
  fmt::print("{}\n", lock_result);

  if (lock_result) {
    fmt::print("{}\n", errno);
  }
  return [shm_name]() { fmt::print("{}\n", ::shm_unlink(shm_name)); };
}

int main(int argc, char **argv) {
  using namespace std::string_view_literals;
  std::signal(SIGINT, [](int) { should_stop = true; });

  if (argc > 1 and argv[1] == "epoll"sv) {
    auto clean = flock_epoll();
    while (not should_stop)
      ;

    clean();
  } else {
    auto clean = flock_shm();
    while (not should_stop)
      ;

    clean();
  }

  (void)EBADF;
}

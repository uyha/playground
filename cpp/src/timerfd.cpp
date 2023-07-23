#include <bits/types/struct_itimerspec.h>
#include <ctime>
#include <fmt/chrono.h>
#include <fmt/printf.h>
#include <poll.h>
#include <sys/poll.h>
#include <sys/timerfd.h>
#include <unistd.h>

int main() {
  auto timer = ::timerfd_create(CLOCK_MONOTONIC, 0);
  auto spec  = ::itimerspec{
       .it_interval = {.tv_sec = 1, .tv_nsec = 0},
       .it_value    = {.tv_sec = 1, .tv_nsec = 0},
  };

  [[maybe_unused]] auto buffer = std::uint64_t{};

  fmt::print("{}:{} {}\n", __FILE__, __LINE__, ::timerfd_settime(timer, 0, &spec, nullptr));

  auto fd = ::pollfd{
      .fd      = timer,
      .events  = POLLIN,
      .revents = {},
  };
  while (true) {
    fmt::print("{}:{} {}\n", __FILE__, __LINE__, ::poll(&fd, 1, -1));
    fmt::print("{}:{} {}\n", __FILE__, __LINE__, std::chrono::system_clock::now());
    fmt::print("{}:{} {}\n", __FILE__, __LINE__, ::read(timer, &buffer, sizeof(buffer)));
    fmt::print("{}:{} {}\n", __FILE__, __LINE__, std::chrono::system_clock::now());
  }
}

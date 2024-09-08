#include <bits/types/struct_itimerspec.h>
#include <ctime>
#include <fmt/chrono.h>
#include <fmt/printf.h>
#include <poll.h>
#include <sys/poll.h>
#include <sys/timerfd.h>
#include <unistd.h>

auto basic() -> void {
  auto timer = ::timerfd_create(CLOCK_MONOTONIC, 0);
  auto spec  = ::itimerspec{
       .it_interval = {.tv_sec = 1, .tv_nsec = 0},
       .it_value    = {.tv_sec = 0, .tv_nsec = 1},
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

auto canceling() -> void {
  auto current = ::timespec{};
  ::clock_gettime(CLOCK_MONOTONIC, &current);

  auto timer = ::timerfd_create(CLOCK_MONOTONIC, 0);
  auto spec  = ::itimerspec{
       .it_interval = {.tv_sec = 0, .tv_nsec = 500'000'000},
       .it_value    = {.tv_sec = 0, .tv_nsec = 500'000'000},
  };

  [[maybe_unused]] auto const cancel = ::itimerspec{
      .it_interval = {.tv_sec = 0, .tv_nsec = 0},
      .it_value    = {.tv_sec = 0, .tv_nsec = 0},
  };

  [[maybe_unused]] auto buffer = std::uint64_t{};

  ::timerfd_settime(timer, 0, &spec, nullptr);

  auto fd = ::pollfd{
      .fd      = timer,
      .events  = POLLIN,
      .revents = {},
  };

  auto ready_to_read = 0;
  while (true) {
    fmt::print("{}:{} {}\n", __FILE__, __LINE__, ready_to_read = ::poll(&fd, 1, -1));

    // Comment out to stop cancelling
    ::timerfd_settime(timer, 0, &cancel, nullptr);

    if (ready_to_read != 0) {
      fmt::print("{}:{} {}\n", __FILE__, __LINE__, ::read(timer, &buffer, sizeof(buffer)));
    }
  }
}

int main() {
  // basic();
  canceling();
}

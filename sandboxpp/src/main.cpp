#include <chrono>
#include <fmt/chrono.h>
#include <fmt/format.h>

using namespace std::chrono;
using namespace std::chrono_literals;

template <typename Duration>
constexpr auto
to_timespec(std::chrono::time_point<std::chrono::system_clock, Duration> const &timepoint) noexcept
    -> ::timespec {
  using namespace std::chrono;
  auto timepoint_s  = time_point_cast<seconds>(timepoint);
  auto timepoint_ns = time_point_cast<nanoseconds>(timepoint);

  auto sec  = timepoint_s.time_since_epoch().count();
  auto nsec = timepoint_ns.time_since_epoch().count()
            - time_point_cast<nanoseconds>(timepoint_s).time_since_epoch().count();

  return {.tv_sec = sec, .tv_nsec = nsec};
}

int main() {
  auto now    = system_clock::time_point{};
  auto dur    = -now.time_since_epoch() - 2s;
  auto now_ns = now + dur;
  /* fmt::print("{}\n", now_ns); */
  fmt::print("{}\n", to_timespec(now_ns).tv_sec);
  fmt::print("{}\n", to_timespec(now_ns).tv_nsec);
}

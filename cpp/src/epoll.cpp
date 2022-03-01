#include <cerrno>
#include <cstdio>
#include <fcntl.h>
#include <fmt/printf.h>
#include <sys/epoll.h>
#include <unistd.h>

int main() {
  auto event  = ::epoll_event{};
  auto epoll  = ::epoll_create1(0);
  auto epoll1 = ::epoll_create1(0);
  {
    auto const error = ::epoll_ctl(epoll, EPOLL_CTL_ADD, epoll1, &event);
    fmt::print("{} {}\n", error, errno == 0);
  }

  {
    auto const error = ::epoll_ctl(epoll1, EPOLL_CTL_ADD, epoll, &event);
    fmt::print("{} {}\n", error, errno == ELOOP);
  }

  {
    auto dir         = ::open(".", O_DIRECTORY);
    auto const error = ::epoll_ctl(epoll, EPOLL_CTL_ADD, dir, &event);

    fmt::print("{} {}\n", error, errno == EPERM);

    ::close(dir);
  }
}

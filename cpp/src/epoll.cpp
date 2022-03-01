#include <cerrno>
#include <cstdio>
#include <fmt/printf.h>
#include <sys/epoll.h>

int main() {
  auto event       = ::epoll_event{};
  auto epoll       = ::epoll_create1(0);
  auto epoll1      = ::epoll_create1(0);
  auto const error = ::epoll_ctl(epoll, EPOLL_CTL_ADD, 7, &event);
  fmt::print("{} {}\n", error, errno);

  auto const error1 = ::epoll_ctl(epoll1, EPOLL_CTL_ADD, epoll, &event);
  fmt::print("{} {}\n", error1, errno);

  (void)EINVAL,(void)ELOOP;
}

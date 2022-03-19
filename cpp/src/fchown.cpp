#include <sys/epoll.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fmt/core.h>

int main(){
  auto epoll = ::epoll_create1(0);

  fmt::print("{}\n", epoll);
  fmt::print("{}\n", ::fchown(epoll, 1000, 1000));
  fmt::print("{}\n", errno);
  fmt::print("{}\n", ::fchmod(epoll, 1000));
  fmt::print("{}\n", errno);
  (void)EBADF;
}

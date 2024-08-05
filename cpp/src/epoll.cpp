#include <cerrno>
#include <cstdio>
#include <fcntl.h>
#include <fmt/ranges.h>
#include <span>
#include <sys/epoll.h>
#include <unistd.h>

int main() {
  auto event = ::epoll_event{
      .events = EPOLLIN,
      .data   = {.fd = STDIN_FILENO},
  };

  auto epoll = ::epoll_create1(0);
  ::epoll_ctl(epoll, EPOLL_CTL_ADD, STDIN_FILENO, &event);

  auto events = std::array<::epoll_event, 1>{};
  auto buffer = std::array<char, 256>{};

  while (true) {
    fmt::print("{}:{}\n", __FILE__, __LINE__);
    (void)::fflush(::stdout);
    auto const count = ::epoll_wait(epoll, events.data(), events.size(), -1);
    (void)count;
    auto const bytes_read = read(STDIN_FILENO, buffer.data(), buffer.size());

    if (bytes_read <= 0) {
      break;
    }

    fmt::print("{}",
               fmt::join(
                   std::span{
                       buffer.begin(),
                       static_cast<decltype(buffer)::size_type>(bytes_read),
                   },
                   ""));
    (void)::fflush(::stdout);
  }
}

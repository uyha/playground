#include <array>
#include <cerrno>
#include <chrono>
#include <fmt/ranges.h>
#include <span>
#include <sys/epoll.h>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>

int main() {
  auto pipes       = std::array<int, 2>{};
  auto pipe_result = ::pipe(pipes.data());

  if (pipe_result == -1) {
    return errno;
  }

  auto const pid = ::fork();

  if (pid == 0) {
    fmt::print("{}:{} {}\n", __FILE__, __LINE__, ::dup2(pipes[1], STDOUT_FILENO));
    fmt::print("{}:{} {}\n", __FILE__, __LINE__, pipes[1]);
    (void)::fflush(::stdout);
    auto const result = ::execlp("journalctl",
                                 "--boot",
                                 "--no-pager",
                                 "--follow",
                                 "--output",
                                 "json-sse",
                                 "--unit",
                                 "zerotier-one.service",
                                 nullptr);
    fmt::print("{}:{} {} {}\n", __FILE__, __LINE__, result, ::strerror(errno));
    (void)::fflush(::stdout);
  } else {
  }

  auto buffer = std::array<char, 256>{};

  auto killthread = std::jthread([&] {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
    ::close(pipes[1]);
  });

  auto events = std::array{
      ::epoll_event{
          .events = EPOLLIN,
          .data   = {.fd = STDIN_FILENO},
      },
      ::epoll_event{
          .events = EPOLLIN,
          .data   = {.fd = pipes[0]},
      },
  };

  auto epoll_fd = ::epoll_create1(0);
  ::epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &events[0]);
  ::epoll_ctl(epoll_fd, EPOLL_CTL_ADD, pipes[0], &events[1]);

  auto event = ::epoll_event{};
  while (true) {
    ::epoll_wait(epoll_fd, &event, 1, -1);
    if (event.data.fd == STDIN_FILENO) {
      auto bytes_read = ::read(STDIN_FILENO, buffer.data(), buffer.size());
      fmt::print("{}:{} {}\n", __FILE__, __LINE__, bytes_read);
      (void)::fflush(::stdout);
      fmt::print("{}",
                 fmt::join(
                     std::span{
                         buffer.data(),
                         static_cast<decltype(buffer)::size_type>(bytes_read),
                     },
                     ""));
    } else {
      auto bytes_read = ::read(pipes[0], buffer.data(), buffer.size());
      if (bytes_read == 0) {
        break;
      }

      fmt::print("{}",
                 fmt::join(
                     std::span{
                         buffer.data(),
                         static_cast<decltype(buffer)::size_type>(bytes_read),
                     },
                     ""));
    }
    (void)::fflush(::stdout);
  }
}

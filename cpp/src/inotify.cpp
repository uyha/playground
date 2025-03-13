#include <array>
#include <fmt/core.h>
#include <sys/inotify.h>
#include <sys/poll.h>

int main() {
  auto handle = inotify_init();

  fmt::print("{}:{} {}\n", __FILE__, __LINE__, handle);
  (void)::fflush(::stdout);

  auto watch_handle = inotify_add_watch(
      handle, "/home/uy/Personal/playground/cpp/asdf", IN_MODIFY | IN_CLOSE_WRITE);
  fmt::print("{}:{} {}\n", __FILE__, __LINE__, watch_handle);
  (void)::fflush(::stdout);

  auto fds = std::array<::pollfd, 1>{
      ::pollfd{.fd = handle, .events = POLLIN, .revents = 0},
  };
  auto event = inotify_event{};

  while (true) {
    ::poll(fds.data(), 1, -1);

    read(handle, &event, sizeof(event));

    fmt::print("{}:{} wd={} mask={} cookie={} len={}\n",
               __FILE__,
               __LINE__,
               event.wd,
               event.mask,
               event.cookie,
               event.len);
    (void)::fflush(::stdout);
  }
}

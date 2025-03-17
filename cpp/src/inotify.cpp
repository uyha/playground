#include <array>
#include <filesystem>
#include <fmt/core.h>
#include <fmt/std.h>
#include <sys/inotify.h>
#include <sys/poll.h>

int main() {
  namespace fs = std::filesystem;

  auto handle = inotify_init();

  fmt::print("{}:{} {}\n", __FILE__, __LINE__, handle);
  (void)::fflush(::stdout);

  auto path         = fs::path{"/home/uy/Personal/playground/cpp/asdf"};
  auto watch_handle = inotify_add_watch(handle, path.parent_path().c_str(), IN_CREATE);
  fmt::print("{}:{} {}\n", __FILE__, __LINE__, watch_handle);
  (void)::fflush(::stdout);

  auto fds = std::array<::pollfd, 1>{
      ::pollfd{.fd = handle, .events = POLLIN, .revents = 0},
  };
  auto buffer = std::array<char, sizeof(inotify_event) + 512>{};

  while (true) {
    auto count = poll(fds.data(), fds.size(), -1);

    fmt::print("count={} fd={} revents={}\n", count, fds[0].fd, fds[0].revents);

    fmt::print("{}\n", read(handle, &buffer, sizeof(buffer)));
    fmt::print("{}\n", errno);

    auto const *event = reinterpret_cast<inotify_event *>(buffer.data());

    fmt::print("{}:{}\n\
wd={}\n\
mask={}\n\
cookie={}\n\
len={}\n\
name={}\n\
path={}\n\
pare={}\n\
same={}\n",
               __FILE__,
               __LINE__,
               event->wd,
               event->mask,
               event->cookie,
               event->len,
               (path.parent_path() / std::string_view{event->name}).string().size(),
               path.string().size(),
               path.parent_path().string().size(),
               (path.parent_path() / std::string_view{event->name}).string().size()
                   == path.string().size());
    (void)::fflush(::stdout);
  }
}

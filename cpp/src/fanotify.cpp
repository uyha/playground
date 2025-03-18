#include <fcntl.h>
#include <fmt/core.h>
#include <fmt/std.h>
#include <sys/fanotify.h>
#include <sys/poll.h>

int main() {
  fmt::print("initializing fanotify\n");

  auto handle = fanotify_init(FAN_CLOEXEC | FAN_CLASS_NOTIF | FAN_REPORT_FID, O_RDONLY);
  if (handle == -1) {
    fmt::print(stderr, "{}\n", strerror(errno));
    return errno;
  }

  fmt::print("marking fanotify\n");

  if (fanotify_mark(handle, FAN_MARK_ADD | FAN_MARK_ONLYDIR, FAN_CLOSE_WRITE, AT_FDCWD, "./")
      == -1) {
    fmt::print(stderr, "{}\n", strerror(errno));
    return errno;
  }
}

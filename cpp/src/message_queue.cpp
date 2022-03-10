#include <fmt/printf.h>
#include <mqueue.h>

int main() {
  auto name  = "/sandbox.queue";
  auto queue = ::mq_open(name, O_RDONLY | O_CREAT | O_EXCL, 0666, nullptr);
  fmt::print("{}\n", queue);

  auto another_queue = ::mq_open(name, O_RDONLY | O_EXCL);
  fmt::print("{}\n", another_queue);

  fmt::print("{}\n", ::mq_unlink(name));
}

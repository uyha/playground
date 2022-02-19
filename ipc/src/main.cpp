#include <cstring>
#include <fmt/printf.h>
#include <mqueue.h>
#include <string>

int main() {
  using namespace std::string_literals;

  auto mq_name = "/sandbox"s;
  auto message_queue = ::mq_open(mq_name.c_str(), O_RDONLY | O_CREAT/*, 0666, nullptr*/);
  if (message_queue == -1) {
    fmt::print(::stderr, "Couldn't open message queue {}\n", mq_name);
    fmt::print(::stderr, "{}\n", std::strerror(errno));
    return errno;
  }

  struct ::mq_attr attr;
  if (mq_getattr(message_queue, &attr) == -1) {
    fmt::print(::stderr, "Couldn't get the attribute of message queue {}\n", mq_name);
    fmt::print(::stderr, "{}\n", std::strerror(errno));
    return errno;
  }

  fmt::print("Maximum # of message on queue:    {}\n", attr.mq_maxmsg);
  fmt::print("Maximum message size:             {}\n", attr.mq_msgsize);
  fmt::print("# of messages currently on queue: {}\n", attr.mq_curmsgs);
  return 0;
}

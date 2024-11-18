#include <cerrno>
#include <string_view>

#include <fmt/std.h>
#include <zmq.hpp>

void server() {
  auto context = zmq::context_t{};
  auto pull    = zmq::socket_t{context, zmq::socket_type::pull};
  pull.bind("ipc://server");

  auto message = zmq::message_t{};

  // while (true) {
  fmt::print("{}\n", pull.recv(message));
  // }
  fmt::print("{}:{}\n", __FILE__, __LINE__);
  (void)::fflush(::stdout);
}
void client() {
  using namespace std::chrono_literals;

  auto context = zmq::context_t{};
  auto poller  = zmq::poller_t<>{};
  auto push    = zmq::socket_t{context, zmq::socket_type::push};
  push.set(zmq::sockopt::immediate, true);
  // push.set(zmq::sockopt::linger, 0);
  // push.set(zmq::sockopt::conflate, true);

  push.connect("ipc://server");

  poller.add(push, zmq::event_flags::pollout);
  auto events = std::vector<decltype(poller)::event_type>{16};

  [[maybe_unused]] auto buffer = zmq::const_buffer{"123", 3};
  while (true) {
    auto count = poller.wait_all(events, -1ms);
    fmt::print("{}:{} {}\n", __FILE__, __LINE__, count);
    (void)::fflush(::stdout);

    // if (count > 0) {
    //   auto result = push.send(buffer, zmq::send_flags::none);
    //   fmt::print("{}:{} {}\n", __FILE__, __LINE__, result);
    //   (void)::fflush(::stdout);
    // }
    // auto result = push.send(buffer, zmq::send_flags::none);
    // fmt::print("{}:{} {}\n", __FILE__, __LINE__, result);
    // (void)::fflush(::stdout);
  }
}

int main(int argc, char **argv) {
  auto target = argc < 2 ? std::string_view{"server"} : std::string_view{argv[1]};

  if (target == "client") {
    client();
    return 0;
  }

  server();
}

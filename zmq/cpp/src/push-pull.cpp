#include <span>
#include <string_view>
#include <thread>

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <zmq.hpp>

auto client() -> void {
  using namespace std::chrono_literals;

  auto context = zmq::context_t{};
  auto poller  = zmq::poller_t<>{};

  auto socket = zmq::socket_t{context, zmq::socket_type::push};
  zmq_socket_monitor(socket.handle(), "inproc://monitor", ZMQ_EVENT_CONNECTED | ZMQ_EVENT_DISCONNECTED);

  auto logger = zmq::socket_t{context, zmq::socket_type::pair};
  logger.connect("inproc://monitor");

  socket.connect("ipc://server");

  poller.add(logger, zmq::event_flags::pollin);

  auto events = std::vector<zmq::poller_event<>>{};
  events.resize(1);

  auto message = zmq::message_t{};
  auto _       = std::jthread([&socket] {
    while (true) {
      socket.send(zmq::const_buffer{"a", 1});
      std::this_thread::sleep_for(1s);
    }
  });

  while (true) {
    auto event_count = poller.wait_all(events, std::chrono::milliseconds{-1});

    for (auto i = 0u; i < event_count; ++i) {
      if (events[i].socket == logger) {
        (void)logger.recv(message);
        fmt::print("event: {:#06x}  \n", message.data<std::uint16_t>()[0]);
        (void)logger.recv(message);
        fmt::print("endpoint: {}\n", message.to_string_view());
      }
    }
  }
}

auto server() -> void {
  auto context = zmq::context_t{};
  auto socket  = zmq::socket_t{context, zmq::socket_type::pull};
  socket.bind("ipc://server");

  auto message = zmq::message_t{};

  while (true) {
    (void)socket.recv(message);
    fmt::print("{::#02x}\n", std::span{message.data<char const>(), message.size()});
    std::this_thread::sleep_for(std::chrono::seconds{1});
  }
}

int main(int argc, char **argv) {
  using namespace std::string_view_literals;

  if (argc < 2) {
    return EINVAL;
  }

  if (argv[1] == "client"sv) {
    client();
  } else if (argv[1] == "server"sv) {
    server();
  } else {
    return EINVAL;
  }
}

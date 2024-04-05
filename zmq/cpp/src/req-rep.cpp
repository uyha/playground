#include <string_view>
#include <thread>

#include <fmt/format.h>
#include <zmq.hpp>

auto client() -> void {
  auto context = zmq::context_t{};
  auto poller  = zmq::poller_t<>{};

  auto socket = zmq::socket_t{context, zmq::socket_type::req};
  zmq_socket_monitor(socket.handle(), "inproc://monitor", ZMQ_EVENT_CONNECTED);

  auto logger = zmq::socket_t{context, zmq::socket_type::pair};
  logger.connect("inproc://monitor");

  socket.set(zmq::sockopt::req_correlate, true);
  socket.set(zmq::sockopt::req_relaxed, true);
  socket.connect("ipc://server");

  poller.add(socket, zmq::event_flags::pollin);
  poller.add(logger, zmq::event_flags::pollin);

  auto events = std::vector<zmq::poller_event<>>{};
  events.resize(2);

  auto message = zmq::message_t{};

  while (true) {
    auto event_count = poller.wait_all(events, std::chrono::milliseconds{-1});

    for (auto i = 0u; i < event_count; ++i) {
      if (events[i].socket == socket) {
        (void)socket.recv(message);
        fmt::print("socket: {}\n", message.to_string_view());
        socket.send(message, zmq::send_flags::none);
      }
      if (events[i].socket == logger) {
        (void)logger.recv(message);
        fmt::print("event: {:#06x}  \n", message.data<std::uint16_t>()[0]);
        if (message.data<std::uint16_t>()[0] == ZMQ_EVENT_CONNECTED) {
          socket.send(zmq::const_buffer{"a", 1});
        }
        (void)logger.recv(message);
        fmt::print("endpoint: {}\n", message.to_string_view());
      }
    }
  }
}

auto server() -> void {
  auto context = zmq::context_t{};
  auto socket  = zmq::socket_t{context, zmq::socket_type::rep};
  socket.bind("ipc://server");

  auto message = zmq::message_t{};

  while (true) {
    (void)socket.recv(message);
    std::this_thread::sleep_for(std::chrono::seconds{1});
    socket.send(message, zmq::send_flags::none);
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

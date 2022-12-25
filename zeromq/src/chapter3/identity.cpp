#include <fmt/printf.h>
#include <zmq.hpp>

auto dump(zmq::socket_t &socket) -> void {
  auto message = zmq::message_t{};
  fmt::print("----------------------------------------\n");
  while (true) {
    assert(socket.recv(message));
    fmt::print("[{:03}] {}\n", message.size(), message.to_string_view());
    if (not message.more()) {
      break;
    }
  }
}

int main() {
  using std::string_literals::operator""s;

  auto context = zmq::context_t{};

  auto sink = zmq::socket_t{context, zmq::socket_type::router};
  sink.bind("inproc://example");

  auto anonymous = zmq::socket_t{context, zmq::socket_type::req};
  anonymous.connect("inproc://example");
  anonymous.send(zmq::message_t{"ROUTER uses a generated 5 byte identity"s}, zmq::send_flags::none);
  dump(sink);

  auto identified = zmq::socket_t{context, zmq::socket_type::req};
  identified.set(zmq::sockopt::routing_id, "peer2");
  identified.connect("inproc://example");
  identified.send(zmq::message_t{"ROUTER uses REQ's socket identity"s}, zmq::send_flags::none);
  dump(sink);
}

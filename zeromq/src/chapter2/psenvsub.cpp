#include <fmt/printf.h>
#include <zmq.hpp>

int main() {
  auto context = zmq::context_t{};

  auto subscriber = zmq::socket_t{context, zmq::socket_type::sub};
  subscriber.connect("tcp://localhost:5563");
  subscriber.set(zmq::sockopt::subscribe, "B");

  auto message = zmq::message_t{};
  while (true) {
    assert((subscriber.recv(message)));
    auto address = message.to_string();

    assert((subscriber.recv(message)));
    auto contents = message.to_string();

    fmt::print("[{}] {}\n", address, contents);
  }
}

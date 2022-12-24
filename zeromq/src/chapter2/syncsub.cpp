#include <fmt/core.h>
#include <zmq.hpp>

int main() {
  auto context = zmq::context_t{};

  auto subscriber = zmq::socket_t{context, zmq::socket_type::sub};
  subscriber.connect("tcp://localhost:5561");
  subscriber.set(zmq::sockopt::subscribe, "");

  auto syncclient = zmq::socket_t{context, zmq::socket_type::req};
  syncclient.connect("tcp://localhost:5562");

  syncclient.send(zmq::const_buffer{"", 0});

  auto message = zmq::message_t{};
  assert((syncclient.recv(message)));

  for (auto updates = 1;; ++updates) {
    assert((subscriber.recv(message)));

    if (message.to_string_view() == "END") {
      fmt::print("Received {} updates\n", updates);
      break;
    }
  }
}

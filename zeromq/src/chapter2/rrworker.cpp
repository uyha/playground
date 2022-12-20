#include <fmt/printf.h>
#include <zmq.hpp>

int main() {
  auto context = zmq::context_t{};

  auto responder = zmq::socket_t{context, zmq::socket_type::rep};
  responder.connect("tcp://localhost:5560");

  auto message = zmq::message_t{};
  while (true) {
    if (responder.recv(message, zmq::recv_flags::none)) {
      fmt::print("Received requets: {}\n", message.to_string_view());
    }

    responder.send(zmq::const_buffer{"World", 5}, zmq::send_flags::none);
  }
}

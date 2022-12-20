#include <fmt/printf.h>
#include <zmq.hpp>

int main() {
  auto context = zmq::context_t{};

  auto requester = zmq::socket_t{context, zmq::socket_type::req};
  requester.connect("tcp://localhost:5559");

  for (auto n = 0; n < 10; ++n) {
    requester.send(zmq::const_buffer{"Hello", 5}, zmq::send_flags::none);

    if (auto message = zmq::message_t{}; requester.recv(message)) {
      fmt::print("Received reply {} {}\n", n, message.to_string_view());
    }
  }
}

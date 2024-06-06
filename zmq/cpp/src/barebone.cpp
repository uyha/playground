#include <zmq.hpp>

int main() {
  auto context = zmq::context_t{};
  auto socket  = zmq::socket_t{context, zmq::socket_type::pull};
  auto message = zmq::message_t{};

  (void)socket.recv(message);
}

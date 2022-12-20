#include <fmt/printf.h>
#include <zmq.hpp>

int main() {
  auto context = zmq::context_t{};

  auto frontend = zmq::socket_t{context, zmq::socket_type::router};
  auto backend  = zmq::socket_t{context, zmq::socket_type::dealer};

  frontend.bind("tcp://*:5559");
  backend.bind("tcp://*:5560");

  zmq::proxy(frontend, backend);
}

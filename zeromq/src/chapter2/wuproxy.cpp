#include <fmt/printf.h>
#include <zmq.hpp>

int main() {
  auto context = zmq::context_t{};

  auto frontend = zmq::socket_t{context, zmq::socket_type::xsub};
  auto backend  = zmq::socket_t{context, zmq::socket_type::xpub};

  frontend.connect("tcp://192.168.55.210:5556");
  backend.connect("tcp://10.1.1.0:8100");

  zmq::proxy(frontend, backend);
}

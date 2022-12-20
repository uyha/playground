#include <fmt/printf.h>
#include <zmq.hpp>

int main() {
  auto context = zmq::context_t{};

  auto receiver = zmq::socket_t{context, zmq::socket_type::pull};
  receiver.connect("tcp://localhost:5557");

  auto sender = zmq::socket_t{context, zmq::socket_type::push};
  sender.connect("tcp://localhost:5558");

  auto controller = zmq::socket_t{context, zmq::socket_type::sub};
  controller.connect("tcp://localhost:5559");
  controller.set(zmq::sockopt::subscribe, "");

  auto items = std::array<zmq::pollitem_t, 2>{
      zmq::pollitem_t{receiver, 0, ZMQ_POLLIN, 0},
      zmq::pollitem_t{controller, 0, ZMQ_POLLIN, 0},
  };
  auto message = zmq::message_t{};
  while (true) {
    zmq::poll(items);

    if (items[0].revents & ZMQ_POLLIN) {
      if (receiver.recv(message)) {
        fmt::print("{}\n", message.to_string_view());
        sender.send(zmq::message_t{"", 0}, zmq::send_flags::none);
      }
    }
    if (items[1].revents & ZMQ_POLLIN) {
      break;
    }
  }
}

#include <zmq.hpp>

int main() {
  auto context = zmq::context_t{};

  auto frontend = zmq::socket_t{context, zmq::socket_type::router};
  auto backend  = zmq::socket_t{context, zmq::socket_type::dealer};

  frontend.bind("tcp://*:5559");
  backend.bind("tcp://*:5560");

  auto items = std::array<zmq::pollitem_t, 2>{
      zmq::pollitem_t{frontend, 0, ZMQ_POLLIN, 0},
      zmq::pollitem_t{backend, 0, ZMQ_POLLIN, 0},
  };

  auto message = zmq::message_t{};
  while (true) {
    zmq::poll(items);

    if (items[0].revents & ZMQ_POLLIN) {
      while (true) {
        if (frontend.recv(message)) {
          auto more = message.more();
          backend.send(message, more ? zmq::send_flags::sndmore : zmq::send_flags::none);
          if (not more) {
            break;
          }
        }
      }
    }

    if (items[1].revents & ZMQ_POLLIN) {
      while (true) {
        if (backend.recv(message)) {
          auto more = message.more();
          frontend.send(message, more ? zmq::send_flags::sndmore : zmq::send_flags::none);
          if (not more) {
            break;
          }
        }
      }
    }
  }
}

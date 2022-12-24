#include <string>
#include <zmq.hpp>

int main() {
  using std::string_literals::operator""s;

  auto context = zmq::context_t{};

  auto publisher = zmq::socket_t{context, zmq::socket_type::pub};
  publisher.bind("tcp://*:5563");

  while (true) {
    publisher.send(zmq::message_t{"A"s}, zmq::send_flags::sndmore);
    publisher.send(zmq::message_t{"We don't want to see this"s}, zmq::send_flags::none);

    publisher.send(zmq::message_t{"B"s}, zmq::send_flags::sndmore);
    publisher.send(zmq::message_t{"We would want to see this"s}, zmq::send_flags::none);
  }
}

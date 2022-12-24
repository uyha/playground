#include <fmt/core.h>
#include <zmq.hpp>

constexpr int subscribers_expected = 10;

int main() {
  auto context = zmq::context_t{};

  auto publisher = zmq::socket_t{context, zmq::socket_type::pub};
  publisher.set(zmq::sockopt::sndhwm, 1100000);
  publisher.bind("tcp://*:5561");

  auto syncservice = zmq::socket_t{context, zmq::socket_type::rep};
  syncservice.bind("tcp://*:5562");

  auto message = zmq::message_t{};
  for (auto subscribers = 0; subscribers < subscribers_expected; ++subscribers) {
    assert((syncservice.recv(message)));
    message.rebuild();
    assert((syncservice.send(message, zmq::send_flags::none)));
  }

  fmt::print("Broadcasting messages\n");

  for (auto n = 0; n < 1000000; ++n) {
    publisher.send(zmq::const_buffer{"Rhubard", 7});
  }
  publisher.send(zmq::const_buffer{"END", 3});
}

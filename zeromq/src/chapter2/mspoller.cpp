#include <chrono>
#include <fmt/printf.h>
#include <fmt/ranges.h>
#include <thread>
#include <zmq.hpp>

int main() {
  using namespace std::chrono_literals;

  auto context = zmq::context_t{};

  auto receiver = zmq::socket_t{context, zmq::socket_type::pull};
  receiver.connect("tcp://localhost:5557");

  auto subscriber = zmq::socket_t{context, zmq::socket_type::sub};
  subscriber.connect("tcp://localhost:5556");
  subscriber.set(zmq::sockopt::subscribe, "1");

  auto items = std::array<zmq::pollitem_t, 2>{zmq::pollitem_t{receiver, 0, ZMQ_POLLIN, 0},
                                              zmq::pollitem_t{subscriber, 0, ZMQ_POLLIN, 0}};

  while (true) {
    auto msg = zmq::message_t{};

    zmq::poll(items);
    if (items[0].revents & ZMQ_POLLIN) {
      if (auto result = subscriber.recv(msg); result) {
        fmt::print("Receiver: {}\n", msg.to_string_view());
      }
    }
    if (items[1].revents & ZMQ_POLLIN) {
      if (auto result = subscriber.recv(msg); result) {
        fmt::print("Subscriber: {}\n", msg.to_string_view());
      }
    }
  }
}

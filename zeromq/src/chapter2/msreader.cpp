#include <chrono>
#include <fmt/printf.h>
#include <fmt/ranges.h>
#include <thread>
#include <zmq.hpp>

int main(int argc, char **argv) {
  using namespace std::chrono_literals;

  auto context = zmq::context_t{};

  auto receiver = zmq::socket_t{context, zmq::socket_type::pull};
  receiver.connect("tcp://localhost:5557");

  auto subscriber = zmq::socket_t{context, zmq::socket_type::sub};
  subscriber.connect("tcp://localhost:5556");
  subscriber.set(zmq::sockopt::subscribe, argc > 1 ? argv[1] : "10001");

  while (true) {
    auto message = zmq::message_t{};

    while (true) {
      if (auto result = receiver.recv(message, zmq::recv_flags::dontwait); result) {
        fmt::print("Receiver: {}\n", message.to_string_view());
      }
    }

    while (true) {
      if (auto result = receiver.recv(message, zmq::recv_flags::dontwait); result) {
        fmt::print("Subscriber: {}\n", message.to_string_view());
      }
    }

    std::this_thread::sleep_for(1ms);
  }
}

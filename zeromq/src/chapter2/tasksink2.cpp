#include <fmt/chrono.h>
#include <fmt/printf.h>
#include <zmq.hpp>

int main() {
  auto context = zmq::context_t{};

  auto receiver = zmq::socket_t{context, zmq::socket_type::pull};
  receiver.bind("tcp://*:5558");

  auto controller = zmq::socket_t{context, zmq::socket_type::pub};
  controller.bind("tcp://*:5559");

  auto message = zmq::message_t{};
  (void)receiver.recv(message, zmq::recv_flags::none);

  auto const start = std::chrono::steady_clock::now();

  for (auto n = 0; n < 100; ++n) {
    if (receiver.recv(message, zmq::recv_flags::none)) {
      if (n % 10 == 0) {
        fmt::print(":");
      } else {
        fmt::print(".");
      }
    }
  }
  fmt::print("Total elapsed time: {} msec\n",
             std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start));

  controller.send(zmq::message_t{"KILL", 4}, zmq::send_flags::none);
}

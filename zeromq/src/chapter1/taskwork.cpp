#include <fmt/printf.h>
#include <sstream>
#include <thread>
#include <zmq.hpp>

int main() {
  using namespace std::chrono_literals;

  namespace chrono = std::chrono;

  auto context  = zmq::context_t{1};
  auto receiver = zmq::socket_t{context, zmq::socket_type::pull};
  receiver.connect("tcp://localhost:5557");

  auto sender = zmq::socket_t{context, zmq::socket_type::push};
  sender.connect("tcp://localhost:5558");

  while (true) {
    auto message = zmq::message_t{};

    if (auto const result = receiver.recv(message); result) {
      fmt::print("Received {} bytes\n", *result);
    }

    auto const message_ptr = static_cast<char *>(message.data());
    auto message_end_ptr   = message_ptr + message.size();
    int workload           = std::strtol(message_ptr, &message_end_ptr, 10);

    std::this_thread::sleep_for(chrono::milliseconds{workload});

    message.rebuild();
    sender.send(message, zmq::send_flags::none);
  }
}

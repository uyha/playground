#include <fmt/chrono.h>
#include <fmt/printf.h>
#include <zmq.hpp>

int main() {
  using namespace std::chrono_literals;

  namespace chrono = std::chrono;
  using clock      = chrono::steady_clock;

  auto context  = zmq::context_t{1};
  auto receiver = zmq::socket_t{context, zmq::socket_type::pull};
  receiver.bind("tcp://*:5558");

  auto message = zmq::message_t{};
  (void)receiver.recv(message, zmq::recv_flags::none);

  auto const start = clock::now();

  for (auto n = 0; n < 100; ++n) {
    (void)receiver.recv(message, zmq::recv_flags::none);
    fmt::print("{}", n % 10 == 0 ? '\n' : '.');
  }

  fmt::print("\nElapsed time: {:%S}ms\n", clock::now() - start);
}

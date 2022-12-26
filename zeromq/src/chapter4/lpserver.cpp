#include <fmt/core.h>
#include <random>
#include <thread>
#include <zmq.hpp>

int main() {
  using std::chrono_literals::operator""ms;

  static auto rand_device = std::random_device();
  static auto rng         = std::mt19937{rand_device()};
  static auto gen         = std::uniform_int_distribution{0, 3};

  auto context = zmq::context_t{};

  auto server = zmq::socket_t{context, zmq::socket_type::rep};
  server.bind("tcp://*:5555");

  auto message = zmq::message_t{};
  for (auto cycles = 0;; ++cycles) {
    assert(server.recv(message));

    if (cycles > 3 and gen(rng) == 0) {
      fmt::print("I: simulating a crash\n");
      break;
    } else if (cycles > 3) {
      fmt::print("I: simulating CPU overload\n");
      std::this_thread::sleep_for(200ms);
    }

    fmt::print("I: normal request ({})\n", message.to_string_view());
    server.send(message, zmq::send_flags::none);
    std::this_thread::sleep_for(100ms);
  }
}

#include <fmt/printf.h>
#include <random>
#include <source_location>
#include <thread>
#include <zmq.hpp>

int main() {
  using std::chrono_literals::operator""ms;

  static auto rand_device  = std::random_device();
  static auto rng          = std::mt19937{rand_device()};
  static auto identity_gen = std::uniform_int_distribution{0, 0x1000};
  static auto problem_gen  = std::uniform_int_distribution{0, 5};

  auto context = zmq::context_t{};

  auto worker         = zmq::socket_t{context, zmq::socket_type::req};
  auto const identity = fmt::format("{:04x}-{:04x}", identity_gen(rng), identity_gen(rng));
  worker.set(zmq::sockopt::routing_id, identity);
  worker.connect("tcp://localhost:5556");

  fmt::print("I: ({}) worker ready\n", identity);
  worker.send(zmq::message_t{std::string{"\001"}}, zmq::send_flags::none);

  auto message = zmq::message_t{};
  for (auto cycles = 0;; ++cycles) {
    assert(worker.recv(message)); // Client identity frame
    auto client_identity = message.to_string();

    if (cycles > 3 and problem_gen(rng) == 0) {
      fmt::print("I: ({}) simulating a crash\n", identity);
      break;
    } else if (cycles > 3) {
      fmt::print("I: ({}) simulating CPU overload\n", identity);
      std::this_thread::sleep_for(300ms);
    }

    fmt::print("I: ({}) normal reply\n", identity);
    std::this_thread::sleep_for(100ms);
    assert(worker.recv(message)); // Client request content frame
    worker.send(zmq::message_t{client_identity}, zmq::send_flags::sndmore);
    worker.send(message, zmq::send_flags::none);
  }
}

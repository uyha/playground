#include <chrono>
#include <fmt/printf.h>
#include <random>
#include <thread>
#include <zmq.hpp>

int main() {
  using namespace std::chrono_literals;

  auto context = zmq::context_t{};

  auto publisher = zmq::socket_t{context, zmq::socket_type::pub};
  publisher.bind("tcp://*:5556");

  auto rand_device     = std::random_device{};
  auto rng             = std::mt19937{rand_device()};
  auto zipcode_gen     = std::uniform_int_distribution<std::mt19937::result_type>{1, 100000};
  auto temperature_gen = std::uniform_int_distribution<int>{-80, 135};
  auto relhumidity_gen = std::uniform_int_distribution<int>{10, 60};
  while (true) {
    auto const zipcode     = zipcode_gen(rng);
    auto const temperature = temperature_gen(rng);
    auto const relhumidity = relhumidity_gen(rng);

    auto update = fmt::format("{:05} {} {}", zipcode, temperature, relhumidity);
    publisher.send(zmq::const_buffer{std::data(update), std::size(update)});

    std::this_thread::sleep_for(5ms);
  }
}

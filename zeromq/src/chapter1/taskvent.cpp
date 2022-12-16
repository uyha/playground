#include <charconv>
#include <chrono>
#include <fmt/chrono.h>
#include <fmt/printf.h>
#include <random>
#include <thread>
#include <zmq.hpp>

int main() {
  using namespace std::chrono_literals;

  namespace chrono = std::chrono;
  using clock      = chrono::steady_clock;

  auto context = zmq::context_t{};
  auto sender  = zmq::socket_t{context, zmq::socket_type::push};
  sender.bind("tcp://*:5557");

  ::getchar();

  auto sink = zmq::socket_t{context, zmq::socket_type::push};
  sink.connect("tcp://localhost:5558");

  auto message = zmq::message_t{2};
  ::memcpy(message.data(), "0", 1);
  sink.send(message, zmq::send_flags::none);

  auto random_device           = std::random_device{};
  auto random_number_generator = std::mt19937{random_device()};
  auto distribution            = std::uniform_int_distribution<std::mt19937::result_type>{1, 100};

  auto total_duration = clock::duration{0};

  for (auto n = 0; n < 100; ++n) {
    auto workload = distribution(random_number_generator);
    total_duration += chrono::milliseconds{workload};

    message.rebuild(10);
    ::memset(message.data(), '\0', 10);
    auto const message_ptr = static_cast<char *>(message.data());
    std::to_chars(message_ptr, message_ptr + 10, workload);
    sender.send(message, zmq::send_flags::none);
  }

  fmt::print("Total expected cost: {:%S}ms\n", total_duration);
  std::this_thread::sleep_for(1s);
}

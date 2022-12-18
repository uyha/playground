#include <chrono>
#include <fmt/printf.h>
#include <fmt/ranges.h>
#include <random>
#include <thread>
#include <zmq.hpp>

int main(int argc, char **argv) {
  using namespace std::chrono_literals;

  auto context = zmq::context_t{};

  auto subscriber = zmq::socket_t{context, zmq::socket_type::sub};
  subscriber.connect("tcp://localhost:5556");
  subscriber.set(zmq::sockopt::subscribe, argc >= 2 ? argv[1] : "10001");

  auto message = zmq::message_t{};
  for (auto i = 0; i < 100; ++i) {
    (void)subscriber.recv(message);
    fmt::print("{}\n", std::string_view{static_cast<char const *>(message.data()), message.size()});
  }
}

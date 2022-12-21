#include <chrono>
#include <fmt/printf.h>
#include <thread>
#include <zmq.hpp>

using namespace std::chrono_literals;

auto worker_routine(zmq::context_t &context) {
  auto receiver = zmq::socket_t{context, zmq::socket_type::rep};
  receiver.connect("inproc://workers");

  auto message = zmq::message_t{};
  while (true) {
    if (receiver.recv(message, zmq::recv_flags::none)) {
      fmt::print("Received request: {}\n", message.to_string_view());
      std::this_thread::sleep_for(1s);
      receiver.send(zmq::const_buffer{"World", 5}, zmq::send_flags::none);
    }
  }
}

int main() {
  auto context = zmq::context_t{};

  auto clients = zmq::socket_t{context, zmq::socket_type::router};
  clients.bind("tcp://*:5555");

  auto workers = zmq::socket_t{context, zmq::socket_type::dealer};
  workers.bind("inproc://workers");

  auto threads = std::array<std::jthread, 5>{
      std::jthread{worker_routine, std::ref(context)},
      std::jthread{worker_routine, std::ref(context)},
      std::jthread{worker_routine, std::ref(context)},
      std::jthread{worker_routine, std::ref(context)},
      std::jthread{worker_routine, std::ref(context)},
  };

  zmq::proxy(clients, workers);
}

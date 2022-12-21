#include <fmt/printf.h>
#include <thread>
#include <zmq.hpp>

auto step1(zmq::context_t &context) {
  auto sender = zmq::socket_t{context, zmq::socket_type::pair};
  sender.connect("inproc://step2");
  sender.send(zmq::const_buffer{"", 0});
}

auto step2(zmq::context_t &context) {
  auto receiver = zmq::socket_t{context, zmq::socket_type::pair};
  receiver.bind("inproc://step2");
  receiver.send(zmq::const_buffer{"", 0});

  auto step1_thread = std::jthread{step1, std::ref(context)};

  auto message      = zmq::message_t{};
  auto const result = receiver.recv(message, zmq::recv_flags::none);
  assert(result);

  auto sender = zmq::socket_t{context, zmq::socket_type::pair};
  sender.connect("inproc://step3");
  sender.send(zmq::const_buffer{"", 0});
}

int main() {
  auto context = zmq::context_t{};

  auto receiver = zmq::socket_t{context, zmq::socket_type::pair};
  receiver.bind("inproc://step3");

  auto step2_thread = std::jthread(step2, std::ref(context));

  auto message      = zmq::message_t{};
  auto const result = receiver.recv(message, zmq::recv_flags::none);
  assert(result);

  fmt::print("Test sucessful\n");
}

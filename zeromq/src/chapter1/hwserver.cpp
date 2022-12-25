#include <chrono>
#include <fmt/printf.h>
#include <thread>
#include <zmq.hpp>

int main() {
  using namespace std::chrono_literals;

  auto context = zmq::context_t{2};
  auto socket  = zmq::socket_t{context, zmq::socket_type::rep};
  socket.bind("tcp://*:5555");

  while (true) {
    zmq::message_t request;

    auto const result = socket.recv(request, zmq::recv_flags::none);
    if (result) {
      fmt::print("{}\n", *result);
    }
    fmt::print("Received Hello\n");

    std::this_thread::sleep_for(1s);

    auto reply = zmq::message_t{5};
    ::memcpy(reply.data(), "World", 5);
    socket.send(reply, zmq::send_flags::none);
  }
}

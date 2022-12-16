#include <chrono>
#include <fmt/format.h>
#include <thread>
#include <zmq.hpp>

int main() {
  using namespace std::chrono_literals;

  auto context = zmq::context_t{2};
  auto socket  = zmq::socket_t{context, zmq::socket_type::req};
  socket.connect("tcp://localhost:5555");

  for (auto n = 0; n != 10; ++n) {
    auto request = zmq::message_t{5};
    ::memcpy(request.data(), "Hello", 5);

    fmt::print("Sending Hello {}...\n", n);
    socket.send(request, zmq::send_flags::none);

    zmq::message_t reply;
    (void)socket.recv(reply, zmq::recv_flags::none);
    fmt::print("Receive World {}\n", n);
  }
}

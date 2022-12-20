#include <csignal>
#include <fcntl.h>
#include <unistd.h>
#include <zmq.hpp>

int signal_fd;

int main() {
  auto context = zmq::context_t{};

  auto socket = zmq::socket_t{context, zmq::socket_type::rep};
  socket.bind("tcp://*:5555");

  auto pipes = std::array<int, 2>{};
  assert(::pipe(std::data(pipes)) == 0);

  for (auto i = 0; i < 2; ++i) {
    auto const flags = ::fcntl(pipes[i], F_GETFL, 0);

    assert(flags >= 0);
    assert(::fcntl(pipes[i], F_SETFL, flags | O_NONBLOCK) == 0);
  }

  signal_fd = std::get<1>(pipes);

  struct ::sigaction action {};
  action.sa_handler = [](int) { assert(::write(signal_fd, " ", 1) == 1); };
  action.sa_flags   = 0;
  ::sigemptyset(&action.sa_mask);
  ::sigaction(SIGINT, &action, nullptr);
  ::sigaction(SIGTERM, &action, nullptr);

  auto items = std::array<zmq::pollitem_t, 2>{
      zmq::pollitem_t{0, std::get<0>(pipes), ZMQ_POLLIN, 0},
      zmq::pollitem_t{socket, 0, ZMQ_POLLIN, 0},
  };

  while (true) {
    try {
      zmq::poll(items);
    } catch (zmq::error_t const &err) {
      assert(err.num() == EINTR);
      continue;
    }

    if (std::get<0>(items).revents & ZMQ_POLLIN) {
      fmt::print("Interrupt received, killing server...\n");
      break;
    }
    if (std::get<1>(items).revents & ZMQ_POLLIN) {
      auto message = zmq::message_t{};
      assert(socket.recv(message, zmq::recv_flags::dontwait) >= 0);
    }
  }
}

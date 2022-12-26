#include <array>
#include <fmt/printf.h>
#include <queue>
#include <zmq.hpp>

int main() {
  auto context = zmq::context_t{};

  auto frontend = zmq::socket_t{context, zmq::socket_type::router};
  frontend.bind("tcp://*:5555");

  auto backend = zmq::socket_t{context, zmq::socket_type::router};
  backend.bind("tcp://*:5556");

  auto workers = std::queue<std::string>{};

  auto items = std::array<zmq::pollitem_t, 2>{zmq::pollitem_t{backend, 0, ZMQ_POLLIN, 0},
                                              zmq::pollitem_t{frontend, 0, ZMQ_POLLIN, 0}};

  auto message = zmq::message_t{};
  while (true) {
    auto poll_client = std::size(workers) > 0;
    assert((zmq::poll(std::data(items), poll_client > 0 ? 2 : 1) != -1));

    if (std::get<0>(items).revents & ZMQ_POLLIN) {
      assert(backend.recv(message)); // Identity frame
      workers.push(message.to_string());

      assert(backend.recv(message)); // Empty delimiter frame

      assert(backend.recv(message));
      if (message.to_string_view() != "\001") { // Client identity frame
        frontend.send(message, zmq::send_flags::sndmore);
        frontend.send(zmq::message_t{}, zmq::send_flags::sndmore);

        assert(backend.recv(message)); // Backend response content frame
        frontend.send(message, zmq::send_flags::none);
      }
    }
    if (std::get<1>(items).revents & ZMQ_POLLIN) {
      assert(frontend.recv(message)); // Identity frame
      auto client_id = message.to_string();

      assert(frontend.recv(message)); // Empty delimiter frame

      auto worker_id = std::move(workers.front());
      workers.pop();

      backend.send(zmq::message_t{worker_id}, zmq::send_flags::sndmore);
      backend.send(zmq::message_t{}, zmq::send_flags::sndmore);
      assert(frontend.recv(message)); // Client request content frame
      backend.send(zmq::message_t(client_id), zmq::send_flags::sndmore);
      backend.send(message, zmq::send_flags::none);
    }
  }
}

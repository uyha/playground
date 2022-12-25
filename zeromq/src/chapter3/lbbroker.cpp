#include <chrono>
#include <fmt/printf.h>
#include <queue>
#include <random>
#include <thread>
#include <zmq.hpp>

using namespace std::string_view_literals;
using namespace std::chrono_literals;

auto set_id(zmq::socket_t &socket) {
  static auto rand_device = std::random_device();
  static auto rng         = std::mt19937{rand_device()};
  static auto gen         = std::uniform_int_distribution{0, 0x10000};

  socket.set(zmq::sockopt::routing_id, fmt::format("{:04x}-{:04x}", gen(rng), gen(rng)));
}

auto client_task() -> void {
  auto context = zmq::context_t{};

  auto client = zmq::socket_t{context, zmq::socket_type::req};
  set_id(client);
  client.connect("ipc://frontend.ipc");

  auto message = zmq::message_t{"HELLO"sv};
  client.send(message, zmq::send_flags::none);
  assert(client.recv(message));
  fmt::print("{}\n", message.to_string_view());
}

auto worker_task() -> void {
  auto context = zmq::context_t{};

  auto worker = zmq::socket_t{context, zmq::socket_type::req};
  set_id(worker);
  worker.connect("ipc://backend.ipc");

  auto message = zmq::message_t{"READY"sv};
  worker.send(message, zmq::send_flags::none);

  while (true) {
    assert(worker.recv(message));
    auto identity = message.to_string();

    assert(worker.recv(message));
    assert(message.to_string_view() == "");

    assert(worker.recv(message));
    fmt::print("Worker: {}\n", message.to_string_view());

    worker.send(zmq::message_t{identity}, zmq::send_flags::sndmore);
    worker.send(zmq::message_t{}, zmq::send_flags::sndmore);
    worker.send(zmq::message_t{"OK"sv}, zmq::send_flags::none);
  }
}

int main() {
  constexpr auto client_number = 10;
  constexpr auto worker_number = 3;

  auto context = zmq::context_t{};

  auto frontend = zmq::socket_t{context, zmq::socket_type::router};
  frontend.bind("ipc://frontend.ipc");

  auto backend = zmq::socket_t{context, zmq::socket_type::router};
  backend.bind("ipc://backend.ipc");

  auto client_threads = std::vector<std::jthread>{};
  for (auto n = 0; n < client_number; ++n) {
    client_threads.emplace_back(client_task);
  }

  auto worker_threads = std::vector<std::jthread>{};
  for (auto n = 0; n < worker_number; ++n) {
    worker_threads.emplace_back(worker_task);
  }

  auto workers = std::queue<std::string>{};
  auto items   = std::array<zmq::pollitem_t, 2>{
      zmq::pollitem_t{backend, 0, ZMQ_POLLIN, 0},
      zmq::pollitem_t{frontend, 0, ZMQ_POLLIN, 0},
  };
  auto message = zmq::message_t{};

  for (auto n = client_number;;) {
    auto poll_client = not workers.empty();
    assert((zmq::poll(std::data(items), poll_client ? 2 : 1, 1s) != -1));

    if (std::get<0>(items).revents & ZMQ_POLLIN) {
      assert(backend.recv(message)); // Identity
      workers.push(message.to_string());

      assert(backend.recv(message)); // Empty delimiter

      assert(backend.recv(message)); // Either client id or READY message

      if (message.to_string_view() != "READY") {
        auto client_id = message.to_string();

        assert(backend.recv(message));
        assert(message.to_string_view() == "");

        assert(backend.recv(message));

        frontend.send(zmq::message_t{client_id}, zmq::send_flags::sndmore);
        frontend.send(zmq::message_t{}, zmq::send_flags::sndmore);
        frontend.send(message, zmq::send_flags::none);
        if (--n == 0) {
          break;
        }
      }
    }

    if (poll_client and std::get<1>(items).revents & ZMQ_POLLIN) {
      assert((frontend.recv(message, zmq::recv_flags::dontwait)));
      auto client_id = message.to_string();

      assert(frontend.recv(message)); // Empty delimiter
      assert(message.to_string_view() == "");

      assert(frontend.recv(message)); // Request

      auto worker_id = workers.front();
      workers.pop();

      backend.send(zmq::message_t{worker_id}, zmq::send_flags::sndmore);
      backend.send(zmq::message_t{}, zmq::send_flags::sndmore);
      backend.send(zmq::message_t{client_id}, zmq::send_flags::sndmore);
      backend.send(zmq::message_t{}, zmq::send_flags::sndmore);
      backend.send(message, zmq::send_flags::none);
    }
  }
}

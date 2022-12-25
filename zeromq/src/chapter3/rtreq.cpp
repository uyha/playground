#include <fmt/printf.h>
#include <random>
#include <thread>
#include <zmq.hpp>

auto set_id(zmq::socket_t &socket) {
  static auto rand_device = std::random_device();
  static auto rng         = std::mt19937{rand_device()};
  static auto gen         = std::uniform_int_distribution{0, 0x10000};

  socket.set(zmq::sockopt::routing_id, fmt::format("{:04x}-{:04x}", gen(rng), gen(rng)));
}

auto worker_task() {
  using std::string_view_literals::operator""sv;
  using std::chrono_literals::operator""ms;

  auto rand_device = std::random_device();
  auto rng         = std::mt19937{rand_device()};
  auto gen         = std::uniform_int_distribution{1, 500};

  auto context = zmq::context_t{};

  auto worker = zmq::socket_t{context, zmq::socket_type::req};
  set_id(worker);
  worker.connect("tcp://localhost:5671");

  auto workload = zmq::message_t{};
  for (auto total = 0;; ++total) {
    worker.send(zmq::message_t{"Hi Boss"sv}, zmq::send_flags::none);
    assert(worker.recv(workload));

    if (workload.to_string_view() == "Fired!") {
      fmt::print("Completed {} tasks\n", total);
      break;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds{gen(rng)});
  }
}

int main() {
  using clock = std::chrono::steady_clock;
  using std::string_view_literals::operator""sv;
  using std::chrono_literals::operator""s;

  constexpr auto worker_number = 10;

  auto context = zmq::context_t{};

  auto broker = zmq::socket_t{context, zmq::socket_type::router};
  broker.bind("tcp://*:5671");

  auto workers = std::vector<std::jthread>{};
  for (auto i = 0; i < worker_number; ++i) {
    workers.emplace_back(worker_task);
  }

  auto start = clock::now();

  auto message = zmq::message_t{};
  for (auto workers_fired = 0;;) {
    assert(broker.recv(message)); // message now contains the identity

    broker.send(message, zmq::send_flags::sndmore);
    broker.send(zmq::message_t{}, zmq::send_flags::sndmore);

    assert(broker.recv(message)); // pop out the empty delimiter
    assert(broker.recv(message)); // pop out the response from worker

    if (clock::now() - start < 5s) {
      broker.send(zmq::message_t{"Work harder"sv}, zmq::send_flags::none);
    } else {
      broker.send(zmq::message_t{"Fired!"sv}, zmq::send_flags::none);
      if (++workers_fired == worker_number) {
        break;
      }
    }
  }
}

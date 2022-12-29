#include <fmt/printf.h>
#include <list>
#include <zmq.hpp>

struct Worker {
  std::string identity;
  std::chrono::steady_clock::time_point last_sent;
};

int main() {
  using std::chrono_literals::operator""ms;
  using clock = std::chrono::steady_clock;

  auto context = zmq::context_t{};

  auto frontend = zmq::socket_t{context, zmq::socket_type::router};
  frontend.bind("tcp://*:5555");

  auto backend = zmq::socket_t{context, zmq::socket_type::router};
  backend.bind("tcp://*:5556");

  auto workers = std::list<Worker>{};
  auto items   = std::array<zmq::pollitem_t, 2>{
      zmq::pollitem_t{backend, 0, ZMQ_POLLIN, 0},
      zmq::pollitem_t{frontend, 0, ZMQ_POLLIN, 0},
  };

  auto last_check = clock::now();
  auto message    = zmq::message_t{};
  while (true) {
    auto const poll_client = not workers.empty();
    assert((zmq::poll(std::data(items), poll_client ? 2 : 1, 3ms) != -1));

    if (std::get<0>(items).revents & ZMQ_POLLIN) {
      assert(backend.recv(message)); // Worker identity frame
      auto identity = message.to_string();

      auto iter = std::find_if(std::begin(workers), std::end(workers), [&identity](auto const &worker) {
        return worker.identity == identity;
      });
      if (iter == std::end(workers)) {
        workers.push_back({.identity = identity, .last_sent = clock::now()});
      } else {
        iter->last_sent = clock::now();
        workers.splice(iter, workers, std::next(iter), std::end(workers));
      }

      assert(backend.recv(message)); // Empty delimiter frame
      assert(backend.recv(message)); // Content frame

      if (message.more()) {
        auto const client_id = message.to_string();
        assert(backend.recv(message)); // Worker response content frame

        frontend.send(zmq::message_t{client_id}, zmq::send_flags::sndmore);
        frontend.send(zmq::message_t{}, zmq::send_flags::sndmore);
        frontend.send(message, zmq::send_flags::none);
      } else {
        auto content = message.to_string_view();
        if (content != "\001" and content != "\002") {
          fmt::print("E: invalid message from worker\n");
          fmt::print("{}\n", content);
        }
      }
    }
    if (poll_client and std::get<1>(items).revents & ZMQ_POLLIN) {
      assert(frontend.recv(message)); // Client identity frame
      auto const client_id = message.to_string();

      assert(frontend.recv(message)); // Empty delimiter frame
      assert(frontend.recv(message)); // Client request content frame

      auto const worker = std::move(workers.front());
      workers.pop_front();

      backend.send(zmq::message_t{worker.identity}, zmq::send_flags::sndmore);
      backend.send(zmq::message_t{}, zmq::send_flags::sndmore);
      backend.send(zmq::message_t{client_id}, zmq::send_flags::sndmore);
      backend.send(message, zmq::send_flags::none);
    }

    if (clock::now() - last_check > 1000ms) {
      for (auto &worker : workers) {
        backend.send(zmq::message_t{worker.identity}, zmq::send_flags::sndmore);
        backend.send(zmq::message_t{}, zmq::send_flags::sndmore);
        backend.send(zmq::message_t{std::string{"\002"}}, zmq::send_flags::none);
      }
    }

    while (not workers.empty() and clock::now() - workers.front().last_sent > 3000ms) {
      fmt::print("I: removing worker {}\n", workers.front().identity);
      workers.pop_front();
    }
  }
}

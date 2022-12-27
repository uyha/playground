#include <fmt/chrono.h>
#include <fmt/core.h>
#include <fmt/printf.h>
#include <random>
#include <zmq.hpp>

constexpr auto liveness = 3;

int main() {
  using std::chrono_literals::operator""ms;
  using clock = std::chrono::steady_clock;

  static auto rand_device = std::random_device();
  static auto rng         = std::mt19937{rand_device()};
  static auto gen         = std::uniform_int_distribution{0, 5};

  auto context = zmq::context_t{};

  auto worker = zmq::socket_t{context, zmq::socket_type::dealer};
  worker.connect("tcp://localhost:5556");

  worker.send(zmq::message_t{}, zmq::send_flags::sndmore);
  worker.send(zmq::message_t{std::string{"\001"}}, zmq::send_flags::none);

  auto current_liveness = liveness;

  auto items          = std::array<zmq::pollitem_t, 1>{zmq::pollitem_t{worker, 0, ZMQ_POLLIN, 0}};
  auto message        = zmq::message_t{};
  auto last_heartbeat = clock::time_point{};
  auto interval       = 1000ms;
  for (auto cycles = 0;;) {
    assert((zmq::poll(items, 1000ms) != -1));

    if (std::get<0>(items).revents & ZMQ_POLLIN) {
      assert(worker.recv(message)); // Empty delimeter frame

      if (not message.more()) {
        fmt::print("E: invalid message\n");
      } else {
        assert(worker.recv(message)); // Either heartbeat or client request

        // If there is no more message, then this should be a heartbeat message
        if (not message.more()) {
          if (message.to_string_view() == "\002") {
            current_liveness = liveness;
          } else {
            fmt::print("E: invalid message\n");
            fmt::print("{}\n", message.to_string_view());
          }
        } else {
          auto client_id = message.to_string();
          assert(worker.recv(message)); // Client request
          if (cycles > 3 and gen(rng) == 0) {
            fmt::print("I: simulating a crash\n");
            break;
          } else if (cycles > 3 and gen(rng) == 1) {
            fmt::print("I: simulating CPU overload\n");
            std::this_thread::sleep_for(3000ms);
          }
          fmt::print("I: normal reply\n");
          assert(worker.send(zmq::message_t{}, zmq::send_flags::sndmore));
          assert(worker.send(zmq::message_t{client_id}, zmq::send_flags::sndmore));
          assert(worker.send(message, zmq::send_flags::none));
          ++cycles;
        }
      }
    } else if (--current_liveness == 0) {
      fmt::print("W: heartbeat failure, can't reach queue\n");
      fmt::print("W: reconnecting in {}\n", interval);
      std::this_thread::sleep_for(interval);

      if (interval < 32000ms) {
        interval *= 2;
      }

      worker = zmq::socket_t{context, zmq::socket_type::dealer};
      worker.connect("tcp://localhost:5556");
      worker.send(zmq::message_t{std::string{"\001"}}, zmq::send_flags::none);
      items = std::array<zmq::pollitem_t, 1>{zmq::pollitem_t{worker, 0, ZMQ_POLLIN, 0}};

      current_liveness = liveness;
    }

    if (clock::now() - last_heartbeat > 1000ms) {
      last_heartbeat = clock::now();
      fmt::print("I: worker heartbeat\n");
      worker.send(zmq::message_t{}, zmq::send_flags::sndmore);
      worker.send(zmq::message_t{std::string{"\002"}}, zmq::send_flags::none);
    }
  }
}

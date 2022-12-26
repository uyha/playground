#include <fmt/printf.h>
#include <zmq.hpp>

constexpr decltype(auto) server_endpoint = "tcp://localhost:5555";

int main() {
  using namespace std::chrono_literals;

  auto context = zmq::context_t{};

  auto client = zmq::socket_t{context, zmq::socket_type::req};
  client.set(zmq::sockopt::linger, 0); // Prevent context to hang forever when destructing
  client.connect(server_endpoint);

  auto sequence = 0;
  fmt::print("Entering while loop...\n");
  for (auto retries_left = 3; retries_left > 0;) {
    client.send(zmq::message_t{fmt::format("{}", ++sequence)}, zmq::send_flags::none);

    while (true) {
      auto items = std::array<zmq::pollitem_t, 1>{zmq::pollitem_t{client, 0, ZMQ_POLLIN, 0}};

      auto rc = zmq::poll(items, 500ms);
      assert(rc != -1);

      if (std::get<0>(items).revents & ZMQ_POLLIN) {
        auto message = zmq::message_t{};
        assert(client.recv(message));

        if (message.to_string_view() == fmt::format("{}", sequence)) {
          fmt::print("I: server replied OK ({})\n", message.to_string_view());
          retries_left = 3;
          break;
        } else {
          fmt::print("E: malformed reply from server: {}\n", message.to_string_view());
        }
      } else {
        if (--retries_left == 0) {
          fmt::print("E: server seems to be offline, abandoning\n");
          break;
        } else {
          fmt::print("W: no response from server, retrying...\n");
          fmt::print("I: reconnecting to server...\n");
          client = zmq::socket_t{context, zmq::socket_type::req};
          client.set(zmq::sockopt::linger, 0); // Prevent context to hang forever when destructing
          client.connect(server_endpoint);
        }
      }
    }
  }
}

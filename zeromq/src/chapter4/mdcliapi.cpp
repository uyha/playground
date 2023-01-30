#include <fmt/core.h>
#include <iterator>
#include <span>
#include <zmq.hpp>

auto const mdpc_client = zmq::message_t{std::string_view{"MDPC01"}};

class MajorDomoClient {
private:
  std::reference_wrapper<zmq::context_t> m_context;
  std::string m_broker;
  zmq::socket_t m_socket;
  bool m_verbose;
  std::chrono::milliseconds m_timeout = std::chrono::milliseconds{2500};
  int m_retries                       = 3;

public:
  MajorDomoClient(zmq::context_t &context, std::string_view broker, bool verbose = false)
      : m_context{context}
      , m_broker{broker}
      , m_socket{m_context, zmq::socket_type::req}
      , m_verbose{verbose} {
    m_socket.connect(m_broker);
  }

  auto connect() {
    m_socket = zmq::socket_t{m_context, zmq::socket_type::req};
    m_socket.connect(m_broker);
    if (m_verbose) {
      fmt::print("I: connecting to broker at {}\n", m_broker);
    }
  }

  auto set_timeout(std::chrono::milliseconds timeout) {
    m_timeout = timeout;
  }

  auto send(std::string_view service, std::span<zmq::message_t const> request_contents) {
    auto frames = std::vector<zmq::message_t>{};
    frames.emplace_back(service);
    frames.emplace_back([&] {
      auto result = zmq::message_t{std::size(mdpc_client)};
      std::memcpy(std::data(result), std::data(mdpc_client), std::size(mdpc_client));
      return result;
    }());

    std::transform(std::begin(request_contents),
                   std::end(request_contents),
                   std::back_inserter(frames),
                   [](auto const &message) {
                     auto result = zmq::message_t{message.size()};
                     std::memcpy(std::data(result), std::data(message), std::size(message));
                     return result;
                   });

    if (m_verbose) {
      fmt::print("I: send request to {} service\n", service);
      for (auto const &frame : request_contents) {
        fmt::print("{}\n", frame.to_string_view());
      }
    }

    auto items = std::array<zmq::pollitem_t, 1>{zmq::pollitem_t{m_socket, 0, ZMQ_POLLIN, 0}};

    for (auto retries_left = m_retries; retries_left > 0;) {
      for (auto i = 0ul; i < std::size(request_contents) - 1; ++i) {
        m_socket.send(frames[i], zmq::send_flags::sndmore);
      }
      m_socket.send(frames[std::size(request_contents) - 1], zmq::send_flags::none);

      assert(zmq::poll(items, m_timeout));
    }
  }
};

int main() {}

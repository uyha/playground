#include <cstdio>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <gzip/gzip.hpp>
#include <msgpack.hpp>
#include <string>
#include <zmq.hpp>

int main() {
  auto str = std::string{};

  while (true) {
    auto c = std::getchar();
    if (c == EOF) {
      break;
    }
    str += (char)c;
  }
  auto context = zmq::context_t{};
  auto sender  = zmq::socket_t{context, zmq::socket_type::push};
  sender.connect("ipc://receiver");

  auto buffer     = std::vector<std::byte>{};
  auto compressor = gzip::Compressor{};
  auto content    = msgpack::sbuffer{};

  msgpack::pack(content, str);
  compressor.compress(buffer, std::span{content.data(), content.size()});
  sender.send(zmq::message_t{buffer.data(), buffer.size()}, zmq::send_flags::none);
  fmt::print("{}\n", str);
  fmt::print("Capacity: {}\n", buffer.capacity());
  fmt::print("Size: {}\n", buffer.size());
}

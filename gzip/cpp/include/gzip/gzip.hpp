#pragma once
#include <cstddef>
#include <span>
#include <stdexcept>
#include <vector>

#include <fmt/core.h>
#include <zlib.h>

namespace gzip {
template <typename T>
concept ByteBuffer = requires(T buffer, std::size_t size) {
  { buffer.data() } -> std::same_as<std::byte *>;
  { buffer.size() } -> std::same_as<std::size_t>;
  { buffer.resize(size) };
};

class Compressor {
public:
  Compressor() {
    m_stream.zalloc = nullptr;
    m_stream.zfree  = nullptr;
    m_stream.opaque = nullptr;

    // 16 tells zlib that GZIP shall be used
    // 15 tells zlib that 2^15 bytes shall be as the window for compressing
    constexpr auto window_bits = 16 + 15;

    // zlib's default value for mem_level
    constexpr auto mem_level = 8;

    auto result =
        ::deflateInit2(&m_stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, window_bits, mem_level, Z_DEFAULT_STRATEGY);

    if (result != Z_OK) {
      switch (result) {
      case Z_MEM_ERROR: throw std::runtime_error("not enough memory");
      case Z_STREAM_ERROR: throw std::runtime_error("invalid parameter");
      case Z_VERSION_ERROR: throw std::runtime_error("incompatible version");
      default: throw std::runtime_error("unknown error");
      }
    }
  }

  template <ByteBuffer TBuffer, typename TData, std::size_t size>
  auto compress(TBuffer &buffer, std::span<TData, size> data) -> void {
    auto bytes = std::as_bytes(data);

    ::deflateReset(&m_stream);
    buffer.resize(0);

    m_stream.next_in   = reinterpret_cast<unsigned char *>(const_cast<std::byte *>(bytes.data()));
    m_stream.avail_in  = bytes.size();
    m_stream.avail_out = 0;

    while (true) {
      if (buffer.size() == m_stream.total_out) {
        buffer.resize(buffer.size() == 0 ? 1024 : buffer.size() * 2);

        m_stream.next_out  = reinterpret_cast<unsigned char *>(buffer.data() + m_stream.total_out);
        m_stream.avail_out = buffer.size() - m_stream.total_out;
      }
      auto deflate_result = ::deflate(&m_stream, Z_FINISH);

      if (deflate_result == Z_STREAM_END) {
        break;
      }
    }

    buffer.resize(m_stream.total_out);
  }

private:
  ::z_stream m_stream{};
};

template <typename TData>
inline auto compress(std::span<TData> data) -> std::vector<std::byte> {
  auto result     = std::vector<std::byte>{};
  auto compressor = Compressor();
  compressor.compress(result, data);
  return result;
}
} // namespace gzip

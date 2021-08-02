#include <cstdint>
#include <cstdio>
#include <utility>

template <typename... u8_t>
void test(std::uint8_t *buffer,
          u8_t... data) requires(std::is_same_v<std::uint8_t, u8_t> &&...) {
  [&]<std::size_t... index>(std::index_sequence<index...>) {
    ((void)(buffer[index] = data), ...);
  }
  (std::make_index_sequence<sizeof...(data)>{});
}

int main() {
  std::uint8_t buffer[2];
  test(buffer, std::uint8_t{1u}, std::uint8_t{1u});
}

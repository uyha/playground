#include <fmt/format.h>

template <std::size_t size>
struct Wrapper {
  char const data[size];
  std::size_t data_size = sizeof(data);
};

template <std::size_t size>
Wrapper(char const (&)[size]) -> Wrapper<size>;

int main() {
  fmt::print("{}\n", Wrapper{"asdjksdaklsfdsfdasfdajhdajhkalsajhklsf"}.data_size);
}

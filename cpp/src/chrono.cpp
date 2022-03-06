#include <chrono>
#include <fmt/printf.h>


int main() {
  using namespace std::chrono_literals;

  fmt::print("{}\n", std::chrono::duration_cast<std::chrono::milliseconds>(-3s).count());
}

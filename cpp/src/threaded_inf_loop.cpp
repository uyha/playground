#include <thread>

int main() {
  auto th = std::jthread([] {
    while (true) {
    }
  });

  while (true) {
  }
}

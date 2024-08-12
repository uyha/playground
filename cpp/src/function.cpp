#include <functional>

int main() {
  std::function<void()> fn = nullptr;
  if (fn) {
    fn();
  }
}

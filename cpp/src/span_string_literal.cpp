#include <span>
#include <vector>

int main() {
  auto vec      = std::vector{"asd", "asd"};
  auto literals = std::span<char const *>(vec);
}

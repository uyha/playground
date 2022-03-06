#include <fmt/core.h>
#define QUOTE(s) #s
#define UNIQUE_IMPL(file, line) file "_" QUOTE(line)
#define UNIQUE UNIQUE_IMPL(__BASE_FILE__, __LINE__)

int main() {
  fmt::print("{}", UNIQUE);
}

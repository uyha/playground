#include <fmt/core.h>
#include <sqlite3.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    fmt::print(stderr, "Expect a path\n");
    return 1;
  }

  sqlite3 *conn = nullptr;
  (void)sqlite3_open(argv[1], &conn);

  char buffer = {};
  (void)fread(&buffer, 1, 1, stdin);
  return 0;
}

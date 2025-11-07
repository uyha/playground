#include <chrono>
#include <fcntl.h>
#include <fmt/chrono.h>
#include <string_view>
#include <sys/file.h>
#include <sys/mman.h>

using namespace std::string_view_literals;

void shm() {
  auto const shm_name = "/sandbox.flock.shm";

  auto shm = ::shm_open(shm_name, O_RDONLY | O_CREAT, 0666);
  fmt::print("shm: {}\n", shm);

  constexpr auto loop = 1'000'000;

  auto const start = std::chrono::steady_clock::now();

  for (auto i = 0; i < loop; ++i) {
    ::flock(shm, LOCK_SH);
    ::flock(shm, LOCK_UN);
  }

  auto const end = std::chrono::steady_clock::now();
  fmt::print("{}\n", (end - start) / loop);
}

void string_compare() {
  auto const s1 =
      "asdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdf"sv;
  auto const s2 =
      "asdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdf"sv;
  auto const start = std::chrono::steady_clock::now();

  (void)(s1 == s2);

  auto const end = std::chrono::steady_clock::now();
  fmt::print("{}\n", end - start);
}

int main(int argc, [[maybe_unused]] char **argv) {
  if (argc > 1) {
    if (argv[1] == "shm"sv) {
      shm();
    }
    if (argv[1] == "string_compare"sv) {
      string_compare();
    }
  }
}

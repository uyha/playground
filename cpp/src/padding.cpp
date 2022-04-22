#include <cstddef>
#include <fmt/format.h>
#include <pthread.h>

template <typename T1, typename T2>
struct pair {
  T1 t1;
  T2 t2;
};

template <typename T>
void print_offset() {
  fmt::print("{} {}\n", std::alignment_of_v<decltype(T::t1)>, std::alignment_of_v<decltype(T::t2)>);
  fmt::print("{} + {} = {}\n", sizeof(T::t1), sizeof(T::t2), sizeof(T));
}

using BoolBool = pair<bool, bool>;

int main() {
  print_offset<pair<uint8_t, uint8_t>>();
  print_offset<pair<uint8_t, uint16_t>>();
  print_offset<pair<uint8_t, uint32_t>>();
  print_offset<pair<uint8_t, uint64_t>>();
  print_offset<pair<uint16_t, uint8_t>>();
  print_offset<pair<uint16_t, uint16_t>>();
  print_offset<pair<uint16_t, uint32_t>>();
  print_offset<pair<uint16_t, uint64_t>>();
  print_offset<pair<uint32_t, uint8_t>>();
  print_offset<pair<uint32_t, uint16_t>>();
  print_offset<pair<uint32_t, uint32_t>>();
  print_offset<pair<uint32_t, uint64_t>>();
  print_offset<pair<uint64_t, uint8_t>>();
  print_offset<pair<uint64_t, uint16_t>>();
  print_offset<pair<uint64_t, uint32_t>>();
  print_offset<pair<uint64_t, uint64_t>>();
  print_offset<pair<::pthread_rwlock_t, uint8_t>>();
  print_offset<pair<::pthread_rwlock_t, uint16_t>>();
  print_offset<pair<::pthread_rwlock_t, uint32_t>>();
  print_offset<pair<::pthread_rwlock_t, uint64_t>>();
  print_offset<pair<pair<uint8_t, uint8_t>, ::pthread_rwlock_t>>();
  print_offset<pair<uint16_t, ::pthread_rwlock_t>>();
  print_offset<pair<uint32_t, ::pthread_rwlock_t>>();
  print_offset<pair<uint64_t, ::pthread_rwlock_t>>();
}

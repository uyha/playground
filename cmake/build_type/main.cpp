#include <cassert>
auto main() -> int {
  assert(false);
#if defined NDEBUG
  return 1;
#else
  return 0;
#endif
}

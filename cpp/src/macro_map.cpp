#include "macro_map.hpp"

#define COMPARE_IMPL(var) var == var;
#define COMPARE(var) EVAL(COMPARE_IMPL(var))
#define MANY_COMPARE(...) EVAL(TRANSFORM(COMPARE, (__VA_ARGS__)))

int main() {
  MANY_COMPARE(1, 2, 3)
}

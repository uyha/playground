#include <stdio.h>

#if defined(__linux__)
#define A 1
#else
#define A 0
#endif

int main() {
  printf("%d\n", A);
}

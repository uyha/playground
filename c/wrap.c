#include <stdint.h>
#include <stdio.h>

int main() {
  uint8_t a = 0xFE;
  uint8_t b = 0x00;
  uint8_t c = b - a;
  printf("%d\n", c);
}

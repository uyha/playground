#include <stdint.h>
#include <stdio.h>

struct RGB {
  uint8_t r, g, b;
};
static inline void ws2812Fill(struct RGB color, uint8_t *dest) {
  // WS2812 accepts BRG not RGB
  uint8_t const bytes[3] = {color.b, color.r, color.g};

  // Expected timer setup:
  // - Running at 8MHz
  // - PWM mode 1
  // We write 3 for the bit 0 and 6 for bit 1. The voltage stays high for:
  // - 0.375 us when CCR is 3
  // - 0.750 us when CCR is 6
  for (uint8_t i = 0; i < 3; ++i) {
    for (uint8_t j = 0; j < 8; ++j) {
      dest[i * 8 + j] = 3 + 3 * ((bytes[i] >> j) & 1u);
    }
  }
}

static inline void ws2812Reset(uint8_t *dest) {}

int main() {
  char const colors[3] = {'B', 'R', 'G'};

  uint8_t buffer[48] = {0};
  struct RGB color = {.r = 0x0F, .g = 0xF0, .b = 0xFF};
  ws2812Fill(color, buffer);

  for (uint8_t i = 0; i < 3; ++i) {
    printf("%c=[", colors[i]);

    for (uint8_t j = 0; j < 7; ++j) {
      printf("%d, ", buffer[i * 8 + j]);
    }
    printf("%d]", buffer[i * 8 + 7]);

    printf("\n");
  }
}

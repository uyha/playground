#include <stdint.h>
#include <stdio.h>

#define UART_DIV_SAMPLING16(_PCLK_, _BAUD_) (((_PCLK_) * 25U) / (4U * (_BAUD_)))
#define UART_DIVMANT_SAMPLING16(_PCLK_, _BAUD_)                                \
  (UART_DIV_SAMPLING16((_PCLK_), (_BAUD_)) / 100U)
#define UART_DIVFRAQ_SAMPLING16(_PCLK_, _BAUD_)                                \
  ((((UART_DIV_SAMPLING16((_PCLK_), (_BAUD_)) -                                \
      (UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) * 100U)) *                  \
     16U) +                                                                    \
    50U) /                                                                     \
   100U)
/* UART BRR = mantissa + overflow + fraction
            = (UART DIVMANT << 4) + (UART DIVFRAQ & 0xF0) + (UART DIVFRAQ &
   0x0FU) */
#define UART_BRR_SAMPLING16(_PCLK_, _BAUD_)                                    \
  (((UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) << 4U) +                      \
    (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0xF0U)) +                   \
   (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0x0FU))

static inline uint16_t fractional_baud_rate(uint32_t clock_frequency,
                                            uint32_t baud_rate) {
  const float usartdiv = clock_frequency / (16.f * baud_rate);
  const uint16_t mantissa = usartdiv;
  const uint8_t fraction = (usartdiv - mantissa) * 16;

  return mantissa << 4 | fraction;
}

int main() {
  printf("%x\n", fractional_baud_rate(8000000, 115200));
  printf("%x\n", UART_BRR_SAMPLING16(8000000, 115200));
}

#include <stdint.h>

void mem_copy(uint8_t *src, uint8_t *dst, uint32_t bytes) {
  for (int i = 0; i < bytes; i++)
    *(dst + i) = *(src + i);
}


#ifndef SYSTICK_H
#define SYSTICK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

  void systickInit (uint16_t frequency);
  void delay (volatile uint32_t count);
  void delay_us (uint32_t t);
  void delay_ms (uint32_t t);
  uint32_t millis (void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif


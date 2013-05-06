#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "hardware.h"
#include "systick.h"

volatile bool crashed = false;

static volatile uint32_t ticks;
static RCC_ClocksTypeDef RCC_Clocks;

void systickInit (uint16_t frequency)
{
  RCC_GetClocksFreq (&RCC_Clocks);
  (void) SysTick_Config (RCC_Clocks.HCLK_Frequency / frequency);
}


// TODO: nasty constant for timing. This value correct for STM32F4 at 72MHz
#define COUNTS_PER_MICROSECOND 24

inline void delay_us (uint32_t microseconds)
{
  uint32_t count;
  count = microseconds * COUNTS_PER_MICROSECOND - 2;
  __ASM volatile (
    "   mov r0, %[count]          \n\t"
    "1: subs r0, #1            \n\t"
    "   bhi 1b                 \n\t"
  :
  : [count] "r" (count)
      : "r0"
    );
}

void delay_ms (uint32_t t)
{
  uint32_t start, end;
  start = millis();
  end = start + t;
  if (start < end) {
    while ( (millis() >= start) && (millis() < end)) {
      // wait
    }
  } else {
    while ( (millis() >= start) || (millis() < end)) {
      // wait
    };
  }
}

// return the system clock as milliseconds
inline uint32_t millis (void)
{
  return ticks;
}



void SysTick_Handler (void)
{
  if (!crashed) {
    STATUS_TOGGLE();
  }
  ticks++;
}
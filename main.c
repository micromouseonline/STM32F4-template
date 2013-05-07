#include <cross_studio_io.h>
#include <stdbool.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "hardware.h"
#include "systick.h"
#include "usart.h"

void status_led_init (void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  // always do this with an auto structure as it is undefined
  GPIO_StructInit (&GPIO_InitStructure);
  STATUS_PORT_CLOCK_INIT (STATUS_PORT_CLOCK, ENABLE);
  GPIO_InitStructure.GPIO_Pin = STATUS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init (STATUS_PORT, &GPIO_InitStructure);
}

// these are the four LEDs on the STM32F4Discovery
void board_leds_init (void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  // always do this with an auto structure as it is undefined
  GPIO_StructInit (&GPIO_InitStructure);
  RCC_AHB1PeriphClockCmd (LED_PORT_CLOCK, ENABLE);
  GPIO_StructInit (&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = ALL_LED_PINS;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init (LED_PORT, &GPIO_InitStructure);
  GPIO_ResetBits (LED_PORT, ALL_LED_PINS);
}


int main (void)
{
  systickInit (1000);
  status_led_init();
  board_leds_init();
  usart_init();
  printf ("\nHello, world!\n");
  while (1) {
    GPIO_SetBits (GREEN_LED);
    delay_ms (100);
    GPIO_SetBits (ORANGE_LED);
    delay_ms (100);
    GPIO_SetBits (RED_LED);
    delay_ms (100);
    GPIO_SetBits (BLUE_LED);
    delay_ms (100);
    GPIO_ResetBits (GPIOD, ALL_LED_PINS);
    delay_ms (100);
  }
  return 0;
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */

void assert_failed (/*@unused@*/uint8_t *file, /*@unused@*/uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  debug_printf ("Assert Fail: file %s on line %d\r\n", file, line);
  crashed = true;
  while (true) {
    STATUS_ON();
    delay_us (100000);
    STATUS_OFF();
    delay_us (100000);
    STATUS_ON();
    delay_us (100000);
    STATUS_OFF();
    delay_us (700000);
  }
}
#endif

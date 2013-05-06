#ifndef HARDWARE_H
#define HARDWARE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

  /*
    A status LED is connected to pin the BOOT1 pin (PB2)
    As we do not boot to RAM, this is always low.
    After boot, the pin can be used as a normal IO and
    act as a status indicator
    TODO: if we try to reprogram when this is set as a high
    output - will there be a problem?
  */
#define STATUS_PIN               GPIO_Pin_2
#define STATUS_PORT              GPIOB
#define STATUS_PORT_CLOCK        RCC_AHB1Periph_GPIOB
#define STATUS_PORT_CLOCK_INIT   RCC_AHB1PeriphClockCmd
#define STATUS                   STATUS_PORT,STATUS_PIN

#define STATUS_ON()      GPIO_SetBits(STATUS);
#define STATUS_OFF()     GPIO_ResetBits(STATUS);
#define STATUS_TOGGLE()  GPIO_ToggleBits(STATUS);

// The LED indicators on the STM32F4Discovery board
#define LED_PORT        GPIOD
#define LED_PORT_CLOCK  RCC_AHB1Periph_GPIOD
#define GREEN_PIN       GPIO_Pin_12
#define ORANGE_PIN      GPIO_Pin_13
#define RED_PIN         GPIO_Pin_14
#define BLUE_PIN        GPIO_Pin_15
#define ALL_LED_PINS    GREEN_PIN | ORANGE_PIN | RED_PIN | BLUE_PIN
#define GREEN_LED       LED_PORT,GREEN_PIN
#define ORANGE_LED      LED_PORT,ORANGE_PIN
#define RED_LED         LED_PORT,RED_PIN
#define BLUE_LED        LED_PORT,BLUE_PIN
#define ALL_LEDS        LED_PORT,ALL_LED_PINS


#ifdef __cplusplus
} // extern "C"
#endif

#endif


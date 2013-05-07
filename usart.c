#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <stm32f4xx.h>
#include "hardware.h"
#include "usart.h"

static bool usart_enabled = false;
/*
 * Simple access to the USART for character I/O.
 *
 * Note that putchar and getchar could be defined to use any peripheral. For
 * example, they could put characters onto an LCD or out over the SPI.
 *
 * Equally, getchar could look at the SPI port or a virtual keypad. Or a
 * combination if you wanted.
 *
 */


/*
 * int putchar(int c) is used normally to put a single character to the console
 * It is the equivalent of using fputc(c,stdout)
 *
 * printf() will use fputc() and hence putchar for its character-by-character
 * output so this is how we tell the system to put out single characters in printf.
 *
 * Simply define this function and printf will send its output, character
 * by character through here. Note that this is slow and will block if
 * the port is not ready. Substitute another suitably configured port
 * if you like.
 *
 * The putchar function has its prototype in stdio.h so there is for one here
 * the Crossworks run time code (in thumb_crt0.s) includes weak declarations
 * of __getchar() and __putchar()
 * by defining them here, you replace those definitions
 *
 * If the character cannot be written for any reason, putchar must return EOF.
 * Just because a character can't be written immediately is not a reason to
 * return EOF: you can busy-wait until the character is ready to be written.
 *
 *  The Rowley documentation is here:
 *
 *   http://www.rowleydownload.co.uk/arm/documentation/libc_customizing_putchar.htm
 *
 */

int __putchar (int ch)
{
  if (!usart_enabled) {
    return EOF;
  }
  while (USART_GetFlagStatus (USART, USART_FLAG_TXE) == RESET);
  USART_SendData (USART, ch);
  return (ch);
}

/*
 * This implemenatation of getchar() will be used by getc(), gets() and so on.
 * It is a poor but simple implementatuion. If characters arrive faster than
 * they can be dealt with, they will be dropped.
 *
 * All in all, you are much better off with an interrupt driven serial comms
 * setup but that is outside the scope of this simple program template.
 *
 * Also, there should be checking of the various status flags for things like
 * parity error, overrun, framing and so on.
 *
 */

int __getchar (void)
{
  if (!usart_enabled) {
    return EOF;
  }
  while (USART_GetFlagStatus (USART1, USART_FLAG_RXNE) == RESET);
  return ( (int) (USART_ReceiveData (USART) & 0xFF));
}


void usart_init (void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  // auto variables have undefined values so be safe
  GPIO_StructInit (&GPIO_InitStructure);
  USART_StructInit (&USART_InitStructure);
  // Make sure the USART and the GPIO port get a clock
  USART_CLK_CMD (USART_CLK, ENABLE);
  USART_GPIO_CLK_CMD (USART_GPIO_CLK, ENABLE);
  // configure the RX and TX pin as AF or nothing will appear
  GPIO_InitStructure.GPIO_Pin = USART_RX_PIN | USART_TX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init (USART_GPIO, &GPIO_InitStructure);
  // Connect USART pins to AF or there was no point in setting them up
  GPIO_PinAFConfig (USART_GPIO, USART_TX_AF_SRC, GPIO_AF_USART);
  GPIO_PinAFConfig (USART_GPIO, USART_RX_AF_SRC, GPIO_AF_USART);
  //Other than the speed, all these are the default values
  USART_InitStructure.USART_BaudRate = USART_BAUD;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  USART_Init (USART, &USART_InitStructure);
  USART_Cmd (USART, ENABLE);
  usart_enabled = true;
}


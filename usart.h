#ifndef	USART_H
#define	USART_H
#include <avr/io.h>
#include <stdint.h>


/* I want the usart initialization to be flexible enough that
 * one can use either the system clock (16 MHz) or to use
 * a special crystal that is tuned for USART. At the same
 * time, I don't want to make it so flexible that it is
 * unusable. Eventually, this will be moved to user.h
 */

#define	BAUDRATE	115200
#define	SERIAL_FREQ	16000000

/* Currently, uart_init will set up the USART in
 * asynchronous normal mode
 */
void usart_init();

void usart_putchar(int c);

char usart_getchar();

#endif

#ifndef	USART_H
#define	USART_H
#include <avr/io.h>
#include <stdint.h>
#include "user.h"
#ifdef	USART_ENABLED

void usart_init();

void usart_putchar(unsigned int c);

unsigned int usart_getchar();
#endif

#endif

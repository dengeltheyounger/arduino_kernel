#ifndef	USART_H
#define	USART_H
#include <avr/io.h>
#include <stdint.h>
#include "user.h"

void usart_init();

void usart_putchar(int c);

char usart_getchar();

#endif

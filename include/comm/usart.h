#ifndef	USART_H
#define	USART_H
#include <stdint.h>
#include <avr/io.h>
#include "sys/mutex.h"

#define	USART_DATA_EMPTY	(1 << 5)
#define	TRANSMITTER_ENABLE	(1 << 3)
#define	TRANSMIT_8_BITS		((1 << 2) | (1 << 1))

#define	STRLEN(X)		((sizeof(X)/sizeof(X[0]))-1)

#define	println_c(U8_DATA)		println(U8_DATA, STRLEN(U8_DATA))

/*
 * For now, we're going to keep it simple and have a simple usart transmitter 
 * that transmits at 9600 8N1. Right now, it's there to debug the kernel.
 */
void usart_init();

void usart_transmit(uint8_t data);

void print(uint8_t *data, uint16_t len);

void println(uint8_t *data, uint16_t len);

#endif

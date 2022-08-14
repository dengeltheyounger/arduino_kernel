#include "comm/usart.h"

/*
 * Asynchronous USART, no parity, 1 stop bit, 8
 * data bits.
 *
 * We set the baud rate to 9600.
 */
void usart_init() {
	uint16_t baudrate = 103;
	UBRR0H = (baudrate >> 8);
	UBRR0L = (baudrate);
	UCSR0B |= TRANSMITTER_ENABLE;
	UCSR0C |= TRANSMIT_8_BITS;
}

void usart_transmit(uint8_t data) {
	while (!(UCSR0A & USART_DATA_EMPTY));

	UDR0 = data;
}

void print(uint8_t *data, uint16_t len) {
	uint16_t i;

	for (i = 0; i < len; ++i) {
		usart_transmit(data[i]);
	}
}

void println(uint8_t *data, uint16_t len) {
	uint16_t i;

	for (i = 0; i < len; ++i) {
		usart_transmit(data[i]);
	}

	usart_transmit((uint8_t) '\n');
	usart_transmit((uint8_t) '\r');
}
	

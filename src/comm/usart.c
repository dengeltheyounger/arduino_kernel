#include "comm/usart.h"

struct mutex usart_mutex = { 
	.held = 0
};

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
	UCSR0B = TRANSMITTER_ENABLE;
	UCSR0C = TRANSMIT_8_BITS;
}

void usart_transmit(uint8_t data) {
	while (!(UCSR0A & USART_DATA_EMPTY));

	UDR0 = data;
}

void print(uint8_t *data, uint16_t len) {
	uint16_t i;

	hold_mutex(&usart_mutex);

	for (i = 0; i < len; ++i) {
		usart_transmit(data[i]);
	}

	release_mutex(&usart_mutex);
}

void println(uint8_t *data, uint16_t len) {
	uint16_t i;

	hold_mutex(&usart_mutex);

	for (i = 0; i < len; ++i) {
		usart_transmit(data[i]);
	}

	usart_transmit((uint8_t) '\n');
	usart_transmit((uint8_t) '\r');

	release_mutex(&usart_mutex);
}
	

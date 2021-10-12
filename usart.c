#include "usart.h"

void usart_init(uint32_t baudrate) {
	// Set baud rate according to data sheet
	uint16_t ubr_val = (uint16_t) ((SERIAL_FREQ / (16 * BAUDRATE)) - 1);
	UBRR0L = (uint8_t) ubr_val;
	UBRR0H = (uint8_t) (ubr_val >> 8);

	// Enable receive and transmitter
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

}

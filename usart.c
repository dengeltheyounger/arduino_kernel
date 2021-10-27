#include "usart.h"

#ifdef	USART_ENABLED

void usart_init() {
	USART_INIT
}

/* These are adapted from the atmega328p datasheet */
void usart_putchar(unsigned int c) { 

	while (!(UCSR0A & (1 << UDRE0)));
	
	// iF 9 bit characters are used, 9th must be written to TXB8
	if (UCSZ0 == 7) {
		// Copy 9th bit to TXB8
		UCSR0B &= ~(1 << TXB8);

		if (c & 0x0100)
			UCSR0B |= (1 << TXB8);
	}

	// Put data into buffer, which sends the data
	UDR0 = c;
}

unsigned int usart_getchar() { 
	// wait for data to be received
	while (!(UCSR0A & (1 << RXC0)));

	if (UCSZ0 == 7) {
		unsigned char status, resh, resl;
		// Get status and ninth bit, then data
		status = UCSR0A;
		resh = UCSR0B;
		resl = UDR0;
		// if error, return -1
		if (status & (1 << FE0) | (1 << DOR0) | (1 << UPE0))
			return -1;
		// filter 9th bit and return
		resh = (resh >> 1) & 0x01;
		return ((resh << 8) | resl);
	}

	else {
		return UDR0;
	}
}

#endif

#endif

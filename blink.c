#include <avr/io.h>
#include <util/delay.h>

static inline void delay_ms(int ms_delay) {
	while (ms_delay--)
		_delay_ms(1);
}

void blink1(void) {
	DDRB |= _BV(DDB5);

	// On for second, off for a second
	while (1) {
		PORTB |= _BV(PORTB5);
		delay_ms(1000);
		PORTB &= ~_BV(PORTB5);
		delay_ms(1000);
	}
}

void blink2(void) {
	DDRB |= _BV(DDB4);

	// Off for a second, on for a second
	while (1) {
		PORTB &= ~_BV(PORTB4);
		delay_ms(1000);
		PORTB |= _BV(PORTB4);
		delay_ms(1000);
	}
}

void blink3(void) {
	DDRB |= _BV(DDB3);

	// Blink twice and then wait a second
	while (1) {
		PORTB |= _BV(PORTB3);
		delay_ms(250);
		PORTB &= ~_BV(PORTB3);
		delay_ms(250);
		PORTB |= _BV(PORTB3);
		delay_ms(250);
		PORTB &= ~_BV(PORTB3);
		delay_ms(1000);

	}
}

void blink4(void) {
	DDRB |= _BV(DDB2);
	int wait_time = 750;
	uint8_t add = 0;

	// oscillate
	while (1) {
		PORTB |= _BV(PORTB2);
		delay_ms(wait_time);
		PORTB &= ~_BV(PORTB2);
		
		if (!add) {
			--wait_time;
		}
		
		else {
			++wait_time;
		}
		
		if (wait_time <= 50) {
			add = 1;
		}

		else if (wait_time >= 750) {
			add = 0;
		}
	}
}

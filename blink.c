#include "blink.h"

void blink1(void) {
	DDRB |= _BV(DDB5);

	// On for second, off for a second
	while (1) {
		PORTB |= _BV(PORTB5);
		task_sleep(1000);
		PORTB &= ~_BV(PORTB5);
		task_sleep(1000);
	}
}

void blink2(void) {
	DDRB |= _BV(DDB4);

	// Off for a second, on for a second
	while (1) {
		PORTB &= ~_BV(PORTB4);
		task_sleep(1000);
		PORTB |= _BV(PORTB4);
		task_sleep(1000);
	}
}

void blink3(void) {
	DDRB |= _BV(DDB3);

	// Blink twice and then wait a second
	while (1) {
		PORTB |= _BV(PORTB3);
		task_sleep(250);
		PORTB &= ~_BV(PORTB3);
		task_sleep(250);
		PORTB |= _BV(PORTB3);
		task_sleep(250);
		PORTB &= ~_BV(PORTB3);
		task_sleep(1000);

	}
}

void blink4(void) {
	DDRB |= _BV(DDB2);
	
	while (1) {
		PORTB |= _BV(PORTB2);
		task_sleep(500);
		PORTB &= ~_BV(PORTB2);
		task_sleep(500);
	}
}

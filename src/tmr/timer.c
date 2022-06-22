#include <avr/interrupt.h>
#include <avr/io.h>
#include "tmr/timer.h"

void set_sys_timer() {

	cli();
	TCNT2 = 0;

	OCR2A = 249;

	TCCR2A |= (1 << WGM21);
	TCCR2B |= (1 << CS22);
	TIMSK2 |= (1 << OCIE2A);
	sei();
}

void set_usr_timer() {
	
	cli();

	TCNT0 = 0;

	OCR0A = 50;

	TCCR0A = 0;
	TCCR0A |= (1 << WGM01);
	TCCR0B |= ((1 << CS11) | (1 << CS10));
	TIMSK0 |= (1 << OCIE0A);
	sei();
}

	

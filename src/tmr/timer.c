#include <avr/interrupt.h>
#include <avr/io.h>
#include "tmr/timer.h"

void set_timer() {

	cli();
	TCNT2 = 0;

	OCR2A = 249;

	TCCR2A |= (1 << WGM21);
	TCCR2B |= (1 << CS22);
	TIMSK2 |= (1 << OCIE2A);
	sei();
}

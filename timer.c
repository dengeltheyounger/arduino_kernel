#include "timer.h"

volatile struct timer system_time;

void set_timer() {

	cli();
	TCCR2A = 0;
	TCCR2B = 0;
	TCNT2 = 0;
	TIFR2 = (1 << OCF2A) | (1 << OCF2B) | (TOV2);

	OCR2A = 249;

	TCCR2A |= (1 << WGM21);
	TCCR2B |= (1 << CS22);
	TIMSK2 |= (1 << OCIE2A);
	sei();
}

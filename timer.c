#include "timer.h"

volatile struct timer system_time;

uint8_t set_timer() {

	TCCR2B = 0;
	TCCR2A = 0;
	TCCR2A |= (1 << WGM21);
	OCR2A = 249;
	TCNT2 = 0;
	TCCR2B |= (1 << CS22);
	
	// Interrupt every ms
	TIMSK2 |= (1 << OCIE2A);

	return 1;
}

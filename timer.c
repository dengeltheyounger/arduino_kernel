#include "timer.h"

struct timer system_time;

uint8_t set_timer() {
	
	// prescalar of 64, ctc mode
	TCCR2B |= (1 << WGM21) | (1 << CS22);
	TCNT2 = 0;
	OCR2A = 249;
	// Interrupt every ms;
	TIMSK2 |= (1 << OCIE2A);

	return 1;
}

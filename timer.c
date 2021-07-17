#include "timer.h"

struct timer system_time;

uint8_t set_timer() {

	TCCR1B |= (1 << WGM12) | (1 << CS10); // no prescaler, ctc mode
	TCNT1 = 0;	// Initialize counter
	OCR1A = 63999;	// Every 4 ms
	TIMSK1 |= (1 << OCIE1A); // Compare interrupt enabled
	TCNT0 = 0;
	TCCR0A = 0; 
	TIMSK0 |= (1 << TOIE0);

	return 1;
}

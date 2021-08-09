#include <avr/interrupt.h>
#include <avr/io.h>

void set_timer() {

	cli();
	TCCR2A = 0;
	TCCR2B = 0;
	TCNT2 = 0;

	OCR2A = 249;

	TCCR2A |= (1 << WGM21);
	TCCR2B |= (1 << CS22);
	TIMSK2 |= (1 << OCIE2A);
	sei();
}

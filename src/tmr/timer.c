#include <avr/interrupt.h>
#include <avr/io.h>
#include "tmr/timer.h"

void set_sys_timer() {

	cli();
	TCNT2 = 0;

	OCR2A = 249;

	TCCR2A = (1 << WGM21);
	TCCR2B = (1 << CS22);
	TIMSK2 = (1 << OCIE2A);
	/* Clear the interrupt flags because somehow that gets set when
	 * setting the mask register.
	 */
	TIFR2 = 0;

#if	DEBUG == 1
	println("Preparing to sei - set_sys_timer",
		STRLEN("Preparing to sei - set_sys_timer"));
#endif
	sei();

#if	DEBUG == 1
	println("sei complete - set_sys_timer",
		STRLEN("sei complete - set_sys_timer"));
#endif

}

void init_timers() {
#if USE_SOFTWARE_TIMER == 1
	init_software_timers();
	set_usr_timer();
#endif

#if	DEBUG == 1
	println("Setting system timer.",
		STRLEN("Setting system timer."));
#endif

	set_sys_timer();

#if	DEBUG == 1
	println("System timer set.",
		STRLEN("System timer set."));
#endif
}

#if USE_SOFTWARE_TIMER == 1

void set_usr_timer() {
	
	cli();

	TCNT0 = 0;

	OCR0A = 50;

	TCCR0A = (1 << WGM01);
	TCCR0B = ((1 << CS11) | (1 << CS10));
	TIMSK0 = (1 << OCIE0A);
	TIFR0 = 0;
	sei();
}

#endif	

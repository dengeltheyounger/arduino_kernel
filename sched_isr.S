#include <avr/io.h>

.section	.text
	.global TIMER1_COMPA_vect

TIMER1_COMPA_vect:
	push	r31
	push	r30
	push	r29
	in	r29,_SFR_IO_ADDR(SREG)
	// Load current and check to see if it is house keeping's task
	lds	r30,in_housekeeper
	cpi	r30,1
	brne	set_housekeeping
	// If house keeping's task, then return
	pop	r29
	out	_SFR_IO_ADDR(SREG),r29
	pop	r29
	pop	r30
	pop	r31
	reti
set_housekeeping:
	// Push the status register onto the stack
	push	r29
	// Set return address to do_housekeeping
	lds	r30,do_housekeeping
	lds	r31,do_housekeeping+1
	push	r30
	push	r31
	reti



	

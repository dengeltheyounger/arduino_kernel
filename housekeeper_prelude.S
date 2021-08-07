#include <avr/io.h>

.section	.text
	.global call_housekeeper

call_housekeeper:
	push	r31
	push	r30
	push	r29
	push	r28
	push	r27
	push	r26
	push	r25
	in	r29,_SFR_IO_ADDR(SREG)
	// Load current and check to see if it is house keeping's task
	lds	r30,in_housekeeping
	cpi	r30,0
	breq	set_housekeeping
	// If house keeping's task, then return
	pop	r29
	out	_SFR_IO_ADDR(SREG),r29
	pop	r25
	pop	r26
	pop	r27
	pop	r28
	pop	r29
	pop	r30
	pop	r31
	ret
set_housekeeping:
	// Push the status register onto the stack
	push	r29
	// Set return address to do_housekeeping
	ldi	r30,lo8(gs(do_housekeeping))
	ldi	r31,hi8(gs(do_housekeeping))
	push	r30
	push	r31
	ret

.section	.bss
	.global mod_four_count,reg_saver

mod_four_count:
	.zero 1

reg_saver:
	.zero 1

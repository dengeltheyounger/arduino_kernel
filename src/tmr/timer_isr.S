#include <avr/io.h>
#include <avr/interrupt.h>
__zero_reg__ = 1

.global TIMER2_COMPA_vect


// The reason why I don't push SREG onto the stack is that the timer isr
// will mostly return to the running task. In that case, shelf it and then
// bring it back. As for pushing and then popping registers, the reason why
// I do that is because the housekeeper can be called independent of the 
// timer ISR. For that reason, I don't make assumptions on what registers
// have been saved in the housekeeper.
TIMER2_COMPA_vect:
	push	r31
	push	r30
	push	r29
	push	r28
	push	r27
	in	r27,_SFR_IO_ADDR(SREG)
	// Use this as the zero register
	push	r1
	clr	r1
	// Load system time
	lds	r28,system_time
	lds	r29,system_time+1
	lds	r30,system_time+2
	lds	r31,system_time+3
	// Add one to 28,29
	adiw	r28,1
	// If overflow, then add one to 26
	adc	r30,__zero_reg__
	// If overflow, then add one to 27
	adc	r31,__zero_reg__
	// Store system time
	sts	system_time,r28
	sts	system_time+1,r29
	sts	system_time+2,r30
	sts	system_time+3,r31
	// Check to see system time % 4 == 0
	lds	r28,mod_four_count
	cpi	r28,3
	// If not, increment and store
	breq	reset_mod_four_count
	inc	r28
	sts	mod_four_count,r28
// Go through process of restoring registers and exiting
cleanup:
	out	_SFR_IO_ADDR(SREG),r27
	pop	r1
	pop	r27
	pop	r28
	pop	r29
	pop	r30
	pop	r31
	reti
// Otherwise, reset counter and then set address of do_housekeeping
reset_mod_four_count:
	sts	mod_four_count,__zero_reg__
	// Restore the remaining registers
	out	_SFR_IO_ADDR(SREG),r27
	pop	r1
	pop	r27
	pop	r28
	pop	r29
	pop	r30
	// Except use r31 to set return address
	pop	r31
	sts	reg_saver,r31
	ldi	r31,lo8(gs(housekeeper_prelude))
	push	r31
	ldi	r31,hi8(gs(housekeeper_prelude))
	push	r31
	lds	r31,reg_saver
	reti

mod_four_count:
	.zero 1

reg_saver:
	.zero 1



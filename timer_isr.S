/*
 * Most of this comes from what GCC outputted. It
 * seems to be a relatively efficient way to handle this.
 */

__zero_reg__ = 1

.section 	.text
	.global TIMER2_COMPA_vect

TIMER2_COMPA_vect:
	push	r1				// 2
	push	r24				// 4
	push	r25				// 6
	push	r26				// 8
	push	r27				// 10
	// This came from gcc
	lds	r24,system_time			// 12
	ldi	r25,lo8(1)			// 13
	add	r25,r24				// 14
	// See if a millisecond has passed
	cpi	r24,lo8(61)			// 15
	breq	update_system_time		// 17
	sts	system_time,r25			// 19
	// Skip the process of updating system time
	rjmp	cleanup				// 21
update_system_time:
	// Clear the zero register
	sts	system_time,__zero_reg__	// 19
	lds	r24,system_time+1		// 21
	lds	r25,system_time+1+1		// 23
	lds	r26,system_time+1+2		// 25
	lds	r27,system_time+1+3		// 27
	// Add one to 24,25
	adiw	r24,1				// 29
	// If overflow, then add one to 26
	adc	r26,__zero_reg__		// 30
	// If overflow, then add one to 27	
	adc	r27,__zero_reg__		// 31
	// Store in Z
	sts	system_time+1,r24		// 33
	sts	system_time+1+1,r25		// 35
	sts	system_time+1+2,r26		// 37
	sts	system_time+1+3,r27		// 39
// Go through process of restoring registers and exiting
cleanup:
	pop	r27				// 23,41
	pop	r26				// 25,43
	pop	r25				// 27,45
	pop	r24				// 29,47
	pop	r1				// 31,49
	reti					// 35,53
/* This ISR takes between 35 and 53 clock cycles to complete.
 * That means that the remaining time is for the function or
 * ISR
 */

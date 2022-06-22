#include <avr/io.h>
#include <avr/interrupt.h>

#define	TIMER_ITERATION_MS	5

__zero_reg__ = 1

.global TIMER2_COMPA_vect

.global TIMER0_COMPA_vect

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

/*
 * This is the software timer interrupt. It does the following:
 * first, it checks to see if a millisecond has passed. If so, it runs through
 * the list of software timers and checks to see if any are ready to be run as
 * a callback. If so, it adds it to the queue. 
 * After that, it checks the queue. If the queue is not empty, then it dequeues
 * and afterwards it pushes the return address on the stack (that way it gets
 * run immediately, and the actual ISR is finished
 */
TIMER0_COMPA_vect:
	// For the software timer
	push	r31
	// And also the status register
	in	r31,_SFR_IO_ADDR(SREG)
	push	r31
	// Back the system timer
	push	r30
	push	r29
	push	r28
	// For the software timer's counter
	push	r27
	push	r26
	push	r25
	push	r24
	// For the timer_counter
	push	r23
	push	r22
	
	// Load the counter to see if we're at a millisecond
	lds	r23,timer_counter
	cpi	r23,TIMER_ITERATION_MS
	brne	check_queue
	// Load the timer pointer array and size
	lds	r29,tmr_arr_size
	lds	r30,tmr_arr_ptr
	lds	r31,tmr_arr_ptr+1
	// Check to see if the timer is stopped. If so, then move on, because
	// the queue is ordered.
check_state:
	ldd	r28,Z+9
	cpi	r28,0
	breq	check_queue
	// Decrement the counter, check to see if it needs to be added.
check_counter:
	ldd	r24,Z+5
	ldd	r25,Z+6
	ldd	r26,Z+7
	ldd	r27,Z+8
	// Subtract 1 from r25 and r26
	sbiw	r24,1
	// If carry, then subtract next from the next
	sbc	r26,__zero_reg__
	sbc	r27,__zero_reg__
	cpi	r24,0
	brne	next_timer
	cpi	r25,0
	brne	next_timer
	cpi	r26,0
	brne	next_timer
	cpi	r27,0
	brne	next_timer

next_timer:
	

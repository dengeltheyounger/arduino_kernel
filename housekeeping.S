#include <avr/io.h>

__zero_reg__ = 1

.section	.bss
task_unavailable:
	.zero 1

.global in_housekeeper
in_housekeeper:
	.zero 1

.section	.text
	.global do_housekeeping

do_housekeeping:
	cli
	// This is for an edge case where the sched_isr happens
	// Immediately after r28 is pushed
	ldi	r28,1
	sts	in_housekeeper,r28
	sei
save_context:
	lds	r28,curr
	lds	r29,curr+1
	std	Y+4,r0
	// Store sreg
	pop	r0
	std	Y+6,r2
	// store r1
	pop	r2
	std	Y+5,r0
	std	Y+7,r3
	std	Y+8,r4
	std	Y+9,r5
	std	Y+10,r6
	std	Y+11,r7
	std	Y+12,r8
	std	Y+13,r9
	std	Y+14,r10
	std	Y+15,r11
	std	Y+16,r12
	std	Y+17,r13
	std	Y+18,r14
	std	Y+19,r15
	std	Y+20,r16
	std	Y+21,r17
	std	Y+22,r18
	std	Y+23,r19
	std	Y+24,r20
	std	Y+25,r21
	std	Y+26,r22
	std	Y+27,r23
	std	Y+28,r24
	// store r25
	pop	r24
	std	Y+29,r24
	// Store r26
	pop	r24
	std	Y+30,r24
	// Store r27
	pop	r24
	std	Y+31,r24
	// Store r28
	pop	r24
	std	Y+32,r24
	// Store r29
	pop	r24
	std	Y+33,r24
	// Store r30
	pop	r24
	std	Y+34,r24
	// Store r31
	pop	r24
	std	Y+35,r24
	// Put SREG back on stack
	push	r0
	// Save the stack pointer
	in	r0,_SFR_IO_ADDR(SPL)
	std	Y+2,r0
	in	r0,_SFR_IO_ADDR(SPH)
	std	Y+3,r0
	// Set aside the original task
	movw	r26,r28
find_task:
	ldd	r30,Y+36
	ldd	r31,Y+37
	movw	r26,r28
find_task_loop:
	// Check if it's null
	cpi	r30,0
	brne	check_task_state
	cpi	r31,0
	brne	check_task_state
	// Load first if we're at the end
	lds	r30,first
	lds	r31,first+1
check_task_state:
	// Load enum
	ldd	r25,Z+38
	// Check to see if it's runnable
	cpi	r25,0
	// If so, load it
	brne	load_next_task
	// Save the task we found
	sts	curr,r30
	sts	curr+1,r31
	// do next set of house keeping
	rjmp	check_list
load_next_task:
	movw	r28,r30
	ldd	r30,Y+36
	ldd	r31,Y+37
	// Make sure that the task we're at is not the original
	cp	r26,r30
	brne	find_task_loop
	cp	r27,r31
	brne	find_task_loop
	// Indicate that all of the tasks are unavailable
	ldi	r25,1
	sts	task_unavailable,r25
	
// Now that we've saved the previous context,
// we're free to play around with the different
// registers without fear of clobbering. Once
// we finish system time stuff, we're going to
// load the new context (provided there's a 
// context to load)

check_list:
	// Load the head of list entry
	lds	r30,head
	lds	r31,head+3
	// Load highest bits of desired time
	ld	r26,Z
	lds	r25,system_time+3
	// Check if system time is greater
	cp	r26,r25
	// If so, skip and find task
	brge	task_runnable
	brlt	next_task
	// Load third 8 bits
	ldd	r26,Z+2
	lds	r25,system_time+2
	cp	r26,r25
	brge	task_runnable
	brlt	next_task
	ldd	r26,Z+1
	lds	r25,system_time+1
	cp	r26,r25
	brge	task_runnable
	brlt	next_task
	ld	r26,Z
	lds	r25,system_time
	cp	r26,r25
	brlt	next_task
task_runnable:
	// Load the task associated with head
	ldd	r28,Z+4
	ldd	r29,Z+4+1
	// Make task runnable
	std	Y+38,__zero_reg__
	// Load next
	ldd	r14,Z+6
	ldd	r15,Z+6+1
	// Prepare to call free
	// Load head as argument for free
	movw	r24,r30
	// Free head
	call	free
	// Next list entry is now head
	sts	head,r14
	sts	head+1,r15
	// Check to see if there's an available task
	lds	r25,task_unavailable
	cpi	r25,1
	// If so, load task and run
	breq	next_task
	// If not, load first task and run first available
	lds	r28,first
	lds	r29,first+1
	rjmp	find_task
next_task:
	// Reset task_unavailable flag
	sts	task_unavailable,__zero_reg__
	lds	r28,curr
	lds	r29,curr+1
	// Load stack pointer for new context
	ldd	r0,Y+2
	out	_SFR_IO_ADDR(SPL),r0
	ldd	r0,Y+3
	out	_SFR_IO_ADDR(SPH),r0
	// Restore SREG. Flags are not changed by these instructions
	pop	r0
	out	_SFR_IO_ADDR(SREG),r0
	// begin restoring GPR
	ldd	r0,Y+4
	// r1 will be restored shortly
	ldd	r2,Y+6
	ldd	r3,Y+7
	ldd	r4,Y+8
	ldd	r5,Y+9
	ldd	r6,Y+10
	ldd	r7,Y+11
	ldd	r8,Y+12
	ldd	r9,Y+13
	ldd	r10,Y+14
	ldd	r11,Y+15
	ldd	r12,Y+16
	ldd	r13,Y+17
	ldd	r14,Y+18
	ldd	r15,Y+19
	ldd	r16,Y+20
	ldd	r17,Y+21
	ldd	r18,Y+22
	ldd	r19,Y+23
	ldd	r20,Y+24
	ldd	r21,Y+25
	ldd	r22,Y+26
	ldd	r23,Y+27
	ldd	r24,Y+28
	ldd	r25,Y+29
	ldd	r26,Y+30
	ldd	r27,Y+31
	// Clobber Z registers so that we can restore Y
	ldd	r30,Y+34
	ldd	r31,Y+35
	push	r30
	push	r31
	ldd	r30,Y+32
	ldd	r31,Y+33
	movw	r28,r30
	pop	r31
	pop	r30
	// We're going to reset the flag so that the interrupt
	// knows that we're finished. However, we want to
	// avoid an edge case where the scheduler interrupt
	// happens right as we set housekeeper_end to 0
	cli
	sts	in_housekeeper,__zero_reg__
	ldd	r1,Y+5
	reti


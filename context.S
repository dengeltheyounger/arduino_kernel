#include <avr/io.h>

.section .text

.global	TIMER1_COMPA_vect

TIMER1_COMPA_vect:
	# Save status register
	push	r31
	push	r30
	in	r30,_SFR_IO_ADDR(SREG)
	push	r30
save_context:
	# Load current struct into Z
	lds	r30, curr
	lds	r31, curr+1
	# Skip the status register for now
	# Begin saving the GPRs
	std	Z+4,r0
	std	Z+5,r1
	std	Z+6,r2
	std	Z+7,r3
	std	Z+8,r4
	std	Z+9,r5
	std	Z+10,r6
	std	Z+11,r7
	std	Z+12,r8
	std	Z+13,r9
	std	Z+14,r10
	std	Z+15,r11
	std	Z+16,r12
	std	Z+17,r13
	std	Z+18,r14
	std	Z+19,r15
	std	Z+20,r16
	std	Z+21,r17
	std	Z+22,r18
	std	Z+23,r19
	std	Z+24,r20
	std	Z+25,r21
	std	Z+26,r22
	std	Z+27,r23
	std	Z+28,r24
	std	Z+29,r25
	std	Z+30,r26
	std	Z+31,r27
	std	Z+32,r28
	std	Z+33,r29
	# Now we have finished storing registers.
	# Pop SREG into r27
	pop	r27
	# Pop r30 into r28, r31 into r29
	pop	r28
	pop	r29
	# Push SREG again to save it on stack
	push	r27
	# Now save Z
	std	Z+34,r28
	std	Z+35,r29
	// Save stack here
	in	r28,_SFR_IO_ADDR(SPL)
	std	Z+2,r28
	in	r28,_SFR_IO_ADDR(SPH)
	std	Z+3,r28
	# Check to see if it's time to run kernel's task
	lds	r5,run_k_task
	tst	r5
	// if not, move to next task
	breq	load_next_task
	# load kernel's task into 28 and 29
	ldi	r28,lo8(k_task)
	ldi	r29,hi8(k_task)
	# set run_k_task to 0
	clr	r5
	sts	run_k_task,r5
	rjmp	get_context
load_next_task:
	# Since run_k_task was 0, we're going to set it to 1
	inc	r5
	sts	run_k_task,r5
	ldd	r28,Z+36
	ldd	r29,Z+37
	# Now we can get the next struct
switch_task:
	# Check to see if r28 is 0
	tst	r28
	# It's a good address if it is not 0. Proceed with switch
	brne	check_state
	# If both 28 and 29 are 0, then the address is null
	tst	r29
	brne	check_state
	# Load first into address. We are setting that as current
	lds	r28,first
	lds	r29,first+1
	# Now curr points to first
check_state:
	# Load enum
	ldd	r25,Y+38
	# Check to see if it is in a runnable state
	tst	r25
	# If the value is zero, then the task is runnable. Load context
	breq	save_curr
	# Load next task and check if it is valid
	ldd	r30,Y+36
	ldd	r31,Y+37
	movw	r28,r30
	jmp	switch_task
save_curr:
	sts	curr, r28
	sts	curr+1,r29
get_context:
	# Unload the stack pointer
	ldd	r0,Y+2
	out	_SFR_IO_ADDR(SPL),r0
	ldd	r0,Y+3
	out	_SFR_IO_ADDR(SPH),r0
	# Restore SREG. Flags are not changed by these instruction
	pop	r0
	out	_SFR_IO_ADDR(SREG),r0
	# Begin storing GPR
	ldd	r0,Y+4
	ldd	r1,Y+5
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
	# We're going to clobber Z, so we'll restore and save it first
	ldd	r30,Y+34
	ldd	r31,Y+35
	push	r30
	push	r31
	# Load r28,r29 into r30,r31. We'll move to r28,r29
	ldd	r30,Y+32
	ldd	r31,Y+33
	# Overwrite struct address
	movw	r28,r30
	# Restore Z registers
	pop	r31
	pop	r30
	# Return to the new task and reset interrupt
	reti

.section .data

run_k_task:
	.byte 1

.section .bss

.global first
	.type	first, @object
	.size 	first, 2
first:
	.zero 2
.global curr
	.type 	curr, @object
	.size 	curr, 2
curr:
	.zero 2
.global k_task
	.type	k_task, @object
	.size	k_task, 2
k_task:
	.zero 2

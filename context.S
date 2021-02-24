#include <avr/io.h>

.global	TIMER1_COMPA_vect

TIMER1_COMPA_vect:
	# Save status register
	push	r0
	in	r0,_SFR_IO_ADDR(SREG)
save_context:
	# Save context
	push	r1
	push	r2
	push	r3
	push	r4
	push	r5
	push	r6
	push	r7
	push	r8
	push	r9
	push	r10
	push	r11
	push	r12
	push	r13
	push	r14
	push	r15
	push	r16
	push	r17
	push	r18
	push	r19
	push	r20
	push	r21
	push	r22
	push	r23
	push	r24
	push	r25
	push	r26
	push	r27
	push	r28
	push	r29
	push	r30
	push	r31
	ldi		r16, 1
	# Save SREG
	push	r0
	# Load current struct into Z
	lds	r30, curr
	lds	r31, curr+1
	// Save stack here
	in	r28,_SFR_IO_ADDR(SPL)
	std	Z+2,r28
	in	r28,_SFR_IO_ADDR(SPH)
	std	Z+3,r28
	# Load the next task to see if it is valid and runnable
	ldd	r28,Z+4
	ldd	r29,Z+5
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
	ldd	r25,Y+6
	# Check to see if it is in a runnable state
	tst	r25
	# If the value is zero, then the task is runnable. Load context
	breq	save_curr
	# Load next task and check if it is valid
	ldd	r30,Y+4
	ldd	r31,Y+5
	movw	r28,r30
	jmp	switch_task
save_curr:
	sts	curr, r28
	sts	curr+1,r29
get_context:
	# Load the new stack
	ldd	r16,Y+2
	out	_SFR_IO_ADDR(SPL),r16
	ldd	r16,Y+3
	out	_SFR_IO_ADDR(SPH),r16
	# Restore SREG. Flags are not changed by these instruction
	pop	r0
	out	_SFR_IO_ADDR(SREG),r0
	pop	r31
	pop	r30
	pop	r29
	pop	r28
	pop	r27
	pop	r26
	pop	r25
	pop	r24
	pop	r23
	pop	r22
	pop	r21
	pop	r20
	pop	r19
	pop	r18
	pop	r17
	pop	r16
	pop	r15
	pop	r14
	pop	r13
	pop	r12
	pop	r11
	pop	r10
	pop	r9
	pop	r8
	pop	r7
	pop	r6
	pop	r5
	pop	r4
	pop	r3
	pop	r2
	pop	r1
	pop	r0
	# Save r16 because we are clobbering it
	push r16
	# Save these registers because we are about to clobber them
	push r30
	push r31
	# Save the status register so we can update stack pointer in struct
	in	r16,_SFR_IO_ADDR(SREG)
	push r16
	in	r16,_SFR_IO_ADDR(SPL)
	# Add 4 for what we just pushed
	subi r16,-4
	# Load curr into Z register
	lds r30,curr
	lds r31,curr+1
	# Save stack pointer
	std Z+2,r16
	in	r16,_SFR_IO_ADDR(SPH)
	# Restore registers
	std	Z+3,r16
	pop	r16
	out	_SFR_IO_ADDR(SREG),r16
	pop	r31
	pop	r30
	pop	r16
	# Return to the new task and reset interrupt
	reti

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
	.section .bss
	.type	k_task, @object
	.size	k_task, 2
k_task:
	.zero 2

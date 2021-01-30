#include <avr/io.h>

TIMER1_COMPA_vect:
	# Save status register
	push	r31
	push	r30
	lds	r30,SREG
	push	r30
	# For whatever reason, sp is an IO register. That means we have to
	# jump through all kinds of hoops to save the darn thing
	push	r28
save_context:
	# Load current struct into Z
	ldi	r30,lo8(curr)
	ldi	r31,hi8(curr)
	# Save the stack pointer
	in	r28,_SFR_IO_ADDR(SPL)
	std	Z+2,r28
	in	r28,_SFR_IO_ADDR(SPH)
	std	Z+3,r28
	# Restore r28 to be saved
	pop	r28
	# Skip the status register for now
	# Begin saving the registers
	std	Z+5,r0
	std	Z+6,r1
	std	Z+7,r2
	std	Z+8,r3
	std	Z+9,r4
	std	Z+10,r5
	std	Z+11,r6
	std	Z+12,r7
	std	Z+13,r8
	std	Z+14,r9
	std	Z+15,r10
	std	Z+16,r11
	std	Z+17,r12
	std	Z+18,r13
	std	Z+19,r14
	std	Z+20,r15
	std	Z+21,r16
	std	Z+22,r17
	std	Z+23,r18
	std	Z+24,r19
	std	Z+25,r20
	std	Z+26,r21
	std	Z+27,r22
	std	Z+28,r23
	std	Z+29,r24
	std	Z+30,r25
	std	Z+31,r26
	std	Z+32,r27
	std	Z+33,r28
	std	Z+34,r29
	# Now we have finished storing registers.
	# Pop SREG into r27
	pop	r27
	# Pop r30 into r28, r31 into r29
	pop	r28
	pop	r29
	# Push SREG again to save it on stack
	push	r27
	# Now save Z
	std	Z+35,r28
	std	Z+36,r29
	# Load the next task to see if it is valid and runnable
	ldd	r28,Z+39
	ldd	r29,Z+40
	# Now we can get the next struct
switch_task:
	# Check to see if r28 is 0
	cpi	r28,0
	# It's a good address if it is not 0. Proceed with switch
	brne	check_state
	# If both 28 and 29 are 0, then the address is null
	cpi	r29,0
	brne	check_state
	# Load first into address. We are setting that as current
	ldi	r28,lo8(first)
	ldi	r29,hi8(first)
	# Now curr points to first
check_state:
	# Load enum
	ldd	r25,Y+41
	# Check to see if it is in a runnable state
	cpi	r25,0
	# If the value is zero, then the task is runnable. Load context
	breq	get_context
	# Load next task and check if it is valid
	ldd	r30,Y+39
	ldd	r31,Y+40
	movw	r28,r30
	jmp	switch_task
get_context:
	# Restore SREG. Flags are not changed by these instruction
	pop	r0
	sts	SREG,r0
	# Resume process of loading context
	ldd	r0,Y+2
	# Note that the stack pointer is an IO register
	out	_SFR_IO_ADDR(SPL),r0
	ldd	r0,Y+3
	out	_SFR_IO_ADDR(SPH),r0
	ldd	r0,Y+5
	ldd	r1,Y+6
	ldd	r2,Y+7
	ldd	r3,Y+8
	ldd	r4,Y+9
	ldd	r5,Y+10
	ldd	r6,Y+11
	ldd	r7,Y+12
	ldd	r8,Y+13
	ldd	r9,Y+14
	ldd	r10,Y+15
	ldd	r11,Y+16
	ldd	r12,Y+17
	ldd	r13,Y+18
	ldd	r14,Y+19
	ldd	r15,Y+20
	ldd	r16,Y+21
	ldd	r17,Y+22
	ldd	r18,Y+23
	ldd	r19,Y+24
	ldd	r20,Y+25
	ldd	r21,Y+26
	ldd	r22,Y+27
	ldd	r23,Y+28
	ldd	r24,Y+29
	ldd	r25,Y+30
	ldd	r26,Y+31
	ldd	r27,Y+32
	# Save registers 30,31. This will hold the address of struct
	push	r30
	push	r31
	ldd	r30,Y+33
	ldd	r31,Y+34
	# Overwrite struct address
	movw	r28,r30
	# Restore Z registers
	pop	r31
	pop	r30
	# Return to the new task and reset interrupt
	reti

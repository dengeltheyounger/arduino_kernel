#include <avr/io.h>

__zero_reg__ = 1
__tmp_reg__ = 0

.section	.bss
	.global in_housekeeping
	.global task_unavailable

task_unavailable:
	.zero 1

in_housekeeping:
	.zero 1

.section	.text
	.global do_housekeeping

do_housekeeping:
	// Clear interrupts in order to set a flag up to indicate
	// That we are in house keeping. Re-enable interrupts after
	// that.
	cli
	ori	r30,0xFF
	sts	in_housekeeping,r30
	sei
save_context:
	lds	r28,curr
	lds	r29,curr+1
	std	Y+4,r0
	std	Y+5,r1
	clr	r1
	// Store sreg
	pop	r0
	std	Y+6,r2
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
	// Go through and check the list to see if item can be removed.
	// Also go through and find new task. Repeat until task can be
	// found
check_wait_list:
	// These portions come from gcc produced assembly. Obviously, there are
	// Optimizations that can be done. I'm not going to worry about that
	// right now.
	lds	r24,head
	lds	r25,head+1
	or	r25,r24
	breq 	get_new_task
check_head:
	lds	r20,system_time
	lds 	r21,system_time+1
	lds 	r22,system_time+2
	lds 	r23,system_time+3
	movw 	r26,r24
	ld 	r16,X+
	ld 	r17,X+
	ld 	r18,X+
	ld 	r19,X
	sbiw 	r26,3
	cp 	r16,r20
	cpc 	r17,r21
	cpc 	r18,r22
	cpc 	r19,r23
	brlo 	store_curr
	breq 	store_curr
	adiw 	r26,6
	ld 	r30,X+
	ld 	r31,X
	sts 	head+1,r31
	sts 	head,r30
	ldd 	__tmp_reg__,Z+4
	ldd 	r31,Z+5
	mov 	r30,__tmp_reg__
	std 	Z+39,__zero_reg__
	std 	Z+38,__zero_reg__
	jmp	free
store_curr:
	lds	r24,curr
	lds	r25,curr+1
get_new_task:
	lds 	r26,curr
	lds 	r27,curr+1
	adiw	r26,36
	ld 	r30,X+
	ld 	r31,X
	sbiw 	r26,36+1
find_runnable_task:
	ldd 	r24,Z+38
	or 	r24,__zero_reg__
	breq 	task_found
	ldd 	__tmp_reg__,Z+36
	ldd 	r31,Z+37
	mov 	r30,__tmp_reg__
	cp 	r30,r24
	cpc 	r31,r25
	brne 	get_new_task
	sts 	curr+1,r31
	sts 	curr,r30
	ldi 	r24,lo8(1)
	sts 	task_unavailable,r24
	jmp 	check_wait_list
task_found:
	sts curr+1,r31
	sts curr,r30
	sts task_unavailable,__zero_reg__	
load_next_task:
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
	// Clobber Z registers so that we can restore Y
	ldd	r30,Y+34
	ldd	r31,Y+35
	push	r30
	push	r31
	ldd	r30,Y+32
	ldd	r31,Y+33
	movw	r28,r30
	pop	r31
	// Set flag down to indicate we are not in house keeping routine
	cli
	ldi	r30,0
	sts	in_housekeeping,r30
	pop	r30
	sei
	ret


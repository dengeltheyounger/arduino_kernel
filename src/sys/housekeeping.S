#include <avr/io.h>
#include <avr/interrupt.h>
__zero_reg__ = 1
__tmp_reg__ = 0

.section	.bss
	.global in_housekeeping
	.global task_unavailable

mod_four_count:
	.zero 1

reg_saver:
	.zero 1

task_unavailable:
	.zero 1

in_housekeeping:
	.zero 1

tmp_stack_ptr:
	.zero 2

.section	.text
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
housekeeper_prelude:
	push	r31
	push	r30
	push	r29
	push	r28
	in	r29,_SFR_IO_ADDR(SREG)
	// Load current and check to see if it is house keeping's task
	lds	r30,in_housekeeping
	cpi	r30,0
	breq	set_housekeeping
	// If house keeping's task, then return
	out	_SFR_IO_ADDR(SREG),r29
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
	std	Y+29,r25
	std	Y+30,r26
	std	Y+31,r27
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
	call	check_req_top
find_task:
	// If get_next_task return 0, then check the request top again.
	// Otherwise, load task
	call	get_next_task
	or	r24,r25
	breq	check_wait_list
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

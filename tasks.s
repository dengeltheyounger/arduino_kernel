	.file	"tasks.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	do_task
	.type	do_task, @function
do_task:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	movw r28,r24
	ldd r30,Y+40
	ldd r31,Y+41
	icall
	ldi r24,lo8(1)
	ldi r25,0
	std Y+39,r25
	std Y+38,r24
.L2:
	rjmp .L2
	.size	do_task, .-do_task
.global	make_task
	.type	make_task, @function
make_task:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	movw r26,r24
	movw r30,r22
	or r24,r25
	breq .L4
	adiw r26,36+1
	st X,r23
	st -X,r22
	sbiw r26,36
.L4:
	std Z+40,r20
	std Z+41,r21
	std Z+29,r31
	std Z+28,r30
	std Z+39,__zero_reg__
	std Z+38,__zero_reg__
/* epilogue start */
	ret
	.size	make_task, .-make_task
.global	set_task_stacks
	.type	set_task_stacks, @function
set_task_stacks:
	push r14
	push r15
	push r16
	push r17
	push r28
	push r29
/* prologue: function */
/* frame size = 0 */
/* stack size = 6 */
.L__stack_usage = 6
	movw r30,r24
	movw r28,r20
	movw r24,r18
	cp r18,r22
	cpc r19,r23
	brlo .L12
	ldd r20,Y+4
	ldd r21,Y+5
	ldi r22,lo8(gs(do_task))
	ldi r23,hi8(gs(do_task))
	mov r17,r23
	movw r18,r20
	subi r18,1
	sbc r19,__zero_reg__
	ld r26,Y
	ldd r27,Y+1
	add r26,r18
	adc r27,r19
	ldi r19,0
	ldi r18,0
.L10:
	cp r18,r24
	cpc r19,r25
	brne .L11
.L13:
	ldi r24,lo8(1)
	ldi r25,0
	rjmp .L8
.L11:
	sbiw r30,0
	breq .L13
	subi r18,-1
	sbci r19,-1
	std Z+1,r27
	st Z,r26
	movw r28,r26
	sbiw r28,1
	std Z+3,r29
	std Z+2,r28
	st X,r22
	ldd r28,Z+2
	ldd r29,Z+3
	movw r14,r28
	ldi r16,1
	sub r14,r16
	sbc r15,__zero_reg__
	std Z+3,r15
	std Z+2,r14
	st Y,r17
	ldd r28,Z+2
	ldd r29,Z+3
	movw r14,r28
	ldi r16,1
	sub r14,r16
	sbc r15,__zero_reg__
	std Z+3,r15
	std Z+2,r14
	st Y,__zero_reg__
	ldd __tmp_reg__,Z+36
	ldd r31,Z+37
	mov r30,__tmp_reg__
	add r26,r20
	adc r27,r21
	rjmp .L10
.L12:
	ldi r25,0
	ldi r24,0
.L8:
/* epilogue start */
	pop r29
	pop r28
	pop r17
	pop r16
	pop r15
	pop r14
	ret
	.size	set_task_stacks, .-set_task_stacks
.global	end_task
	.type	end_task, @function
end_task:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ldi r18,lo8(1)
	ldi r19,0
	movw r30,r24
	std Z+39,r19
	std Z+38,r18
/* epilogue start */
	ret
	.size	end_task, .-end_task
.global	k_task
	.section .bss
	.type	k_task, @object
	.size	k_task, 2
k_task:
	.zero	2
.global	first
	.type	first, @object
	.size	first, 2
first:
	.zero	2
.global	curr
	.type	curr, @object
	.size	curr, 2
curr:
	.zero	2
	.ident	"GCC: (Gentoo 10.3.0-r1 p2) 10.3.0"
.global __do_clear_bss

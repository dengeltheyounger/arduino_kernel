	.file	"arduino_kernel.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	kernel_main
	.type	kernel_main, @function
kernel_main:
	push r4
	push r5
	push r6
	push r7
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
	push r16
	push r17
	push r28
	push r29
	in r28,__SP_L__
	in r29,__SP_H__
	sbiw r28,50
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
/* prologue: function */
/* frame size = 50 */
/* stack size = 66 */
.L__stack_usage = 66
	movw r6,r22
	movw r4,r20
	in r18,__SP_L__
	in r19,__SP_H__
	std Y+50,r19
	std Y+49,r18
	cpi r24,lo8(5)
	brlo .+2
	rjmp .L11
	mov r14,r24
	mov r15,__zero_reg__
	ldi r19,lo8(42)
	mul r24,r19
	movw r20,r0
	clr __zero_reg__
	movw r24,r20
	clr r24
	andi r25,240
	in r30,__SP_L__
	in r31,__SP_H__
	sub r30,r24
	sbc r31,r25
	movw r24,r30
.L3:
	in r18,__SP_L__
	in r19,__SP_H__
	cp r18,r24
	cpc r19,r25
	breq .L4
	in r30,__SP_L__
	in r31,__SP_H__
	subi r31,16
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r31
	out __SREG__,__tmp_reg__
	out __SP_L__,r30
	subi r30,1
	sbci r31,-16
	st Z,__zero_reg__
	rjmp .L3
.L4:
	movw r24,r20
	andi r25,15
	in r18,__SP_L__
	in r19,__SP_H__
	sub r18,r24
	sbc r19,r25
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r19
	out __SREG__,__tmp_reg__
	out __SP_L__,r18
	sbiw r24,0
	breq .L5
	sbiw r24,1
	in r30,__SP_L__
	in r31,__SP_H__
	add r30,r24
	adc r31,r25
	st Z,__zero_reg__
.L5:
	in r16,__SP_L__
	in r17,__SP_H__
	subi r16,-1
	sbci r17,-1
	movw r24,r28
	adiw r24,1
	movw r8,r24
	sts k_task+1,r25
	sts k_task,r24
	ldi r23,0
	ldi r22,0
	movw r24,r16
	call memset
	ldi r24,lo8(42)
	movw r30,r8
	0:
	st Z+,__zero_reg__
	dec r24
	brne 0b
	movw r10,r16
	mov r13,__zero_reg__
	mov r12,__zero_reg__
.L6:
	cp r14,r12
	cpc r15,r13
	breq .+2
	rjmp .L9
	sts first+1,r17
	sts first,r16
	std Y+40,r17
	std Y+39,r16
	ldi r24,lo8(-1)
	ldi r25,lo8(8)
	std Y+2,r25
	std Y+1,r24
	ldi r24,lo8(1)
	ldi r25,0
	std Y+42,r25
	std Y+41,r24
	sts curr+1,r9
	sts curr,r8
	std Y+48,__zero_reg__
	std Y+47,__zero_reg__
	movw r22,r4
	movw r24,r14
	call calloc
	std Y+44,r25
	std Y+43,r24
	or r24,r25
	breq .L11
	std Y+46,r15
	std Y+45,r14
	std Y+47,r4
	std Y+48,r5
	movw r18,r14
	movw r20,r28
	subi r20,-43
	sbci r21,-1
	movw r22,r14
	movw r24,r16
	call set_task_stacks
	or r24,r25
	breq .+2
	rjmp .L10
	ldd r24,Y+43
	ldd r25,Y+44
	call free
.L11:
	ldi r25,0
	ldi r24,0
	ldd r30,Y+49
	ldd r31,Y+50
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r31
	out __SREG__,__tmp_reg__
	out __SP_L__,r30
/* epilogue start */
	adiw r28,50
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r29
	pop r28
	pop r17
	pop r16
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop r7
	pop r6
	pop r5
	pop r4
	ret
.L9:
	cpse r12,__zero_reg__
	rjmp .L7
	movw r30,r6
	ld r20,Z
	ldd r21,Z+1
	movw r22,r16
	ldi r25,0
	ldi r24,0
.L19:
	call make_task
	ldi r31,-1
	sub r12,r31
	sbc r13,r31
	ldi r18,42
	add r10,r18
	adc r11,__zero_reg__
	rjmp .L6
.L7:
	movw r30,r12
	lsl r30
	rol r31
	add r30,r6
	adc r31,r7
	ld r20,Z
	ldd r21,Z+1
	movw r22,r10
	movw r24,r10
	sbiw r24,42
	rjmp .L19
.L10:
	call set_timer
/* #APP */
 ;  67 "arduino_kernel.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
.L12:
	rjmp .L12
	.size	kernel_main, .-kernel_main
	.ident	"GCC: (Gentoo Hardened 9.3.0-r2 p4) 9.3.0"

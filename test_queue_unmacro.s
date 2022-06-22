	.file	"test_queue_unmacro.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	foo
	.type	foo, @function
foo:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
/* epilogue start */
	ret
	.size	foo, .-foo
.global	baz
	.type	baz, @function
baz:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
/* epilogue start */
	ret
	.size	baz, .-baz
.global	bar
	.type	bar, @function
bar:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
/* epilogue start */
	ret
	.size	bar, .-bar
.global	enqueue
	.type	enqueue, @function
enqueue:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	movw r26,r24
	adiw r26,1
	ld r30,X
	sbiw r26,1
	ld r24,X
	cp r30,r24
	brsh .L7
	ldi r24,lo8(1)
	add r24,r30
	adiw r26,1
	st X,r24
	sbiw r26,1
	ldi r31,0
	lsl r30
	rol r31
	add r30,r26
	adc r31,r27
	std Z+3,r22
	std Z+4,r23
	ldi r24,lo8(1)
	ldi r25,0
	ret
.L7:
	ldi r24,0
	ldi r25,0
/* epilogue start */
	ret
	.size	enqueue, .-enqueue
.global	dequeue
	.type	dequeue, @function
dequeue:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	movw r26,r24
	adiw r26,2
	ld r30,X
	sbiw r26,2
	adiw r26,1
	ld r24,X
	sbiw r26,1
	cp r30,r24
	brsh .L10
	ldi r24,lo8(1)
	add r24,r30
	adiw r26,2
	st X,r24
	sbiw r26,2
	ldi r31,0
	lsl r30
	rol r31
	add r30,r26
	adc r31,r27
	ldd r24,Z+3
	ldd r25,Z+4
	ret
.L10:
	ldi r24,0
	ldi r25,0
/* epilogue start */
	ret
	.size	dequeue, .-dequeue
.global	fun
	.type	fun, @function
fun:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	lds r24,q+1
	lds r25,q
	cp r24,r25
	brsh .L11
	ldi r26,lo8(1)
	add r26,r24
	sts q+1,r26
	mov r30,r24
	ldi r31,0
	lsl r30
	rol r31
	subi r30,lo8(-(q))
	sbci r31,hi8(-(q))
	ldi r18,lo8(gs(foo))
	ldi r19,hi8(gs(foo))
	std Z+4,r19
	std Z+3,r18
	cp r26,r25
	brsh .L11
	ldi r30,lo8(2)
	add r30,r24
	sts q+1,r30
	ldi r27,0
	lsl r26
	rol r27
	subi r26,lo8(-(q))
	sbci r27,hi8(-(q))
	ldi r18,lo8(gs(bar))
	ldi r19,hi8(gs(bar))
	adiw r26,3+1
	st X,r19
	st -X,r18
	sbiw r26,3
	cp r30,r25
	brsh .L11
	subi r24,lo8(-(3))
	sts q+1,r24
	ldi r31,0
	lsl r30
	rol r31
	subi r30,lo8(-(q))
	sbci r31,hi8(-(q))
	ldi r24,lo8(gs(baz))
	ldi r25,hi8(gs(baz))
	std Z+4,r25
	std Z+3,r24
.L11:
/* epilogue start */
	ret
	.size	fun, .-fun
.global	q
	.data
	.type	q, @object
	.size	q, 9
q:
	.byte	3
	.byte	0
	.byte	0
	.word	0
	.word	0
	.word	0
	.ident	"GCC: (Gentoo 12.1.1_p20220604 p7) 12.1.1 20220604"
.global __do_copy_data

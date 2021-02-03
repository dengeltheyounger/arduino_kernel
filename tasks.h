#ifndef	TASKS_H
#define	TASKS_H
#include <stdlib.h>
#include <stdint.h>
#include "stack.h"
#include "uart.h"
#include <stdio.h>
#include <avr/io.h>
#ifndef	DEBUG
#define	DEBUG
#endif

/* Right now there are only two
 * task states. The only possible
 * reason why this would be necessary
 * is if the programmer had a task
 * that could end, and wanted to use
 * the stack space of that task later.
 */
typedef enum task_state {
	runnable = 0,
	complete = 1
} task_state;

struct context {
	void *sp_start;
	void *sp;
	uint8_t r0;
	/* r1 should always contain zero. Must be saved during ISR prologue. Must be zeroed out during
	 * the ISR routine. Must be restored during ISR epilogue
	 */
	uint8_t r1;
	uint8_t r2;
	uint8_t r3;
	uint8_t r4;
	uint8_t r5;
	uint8_t r6;
	uint8_t r7;
	uint8_t r8;
	uint8_t r9;
	uint8_t r10;
	uint8_t r11;
	uint8_t r12;
	uint8_t r13;
	uint8_t r14;
	uint8_t r15;
	uint8_t r16;
	uint8_t r17;
	uint8_t r18;
	uint8_t r19;
	uint8_t r20;
	uint8_t r21;
	uint8_t r22;
	uint8_t r23;
	uint8_t r24;
	uint8_t r25;
	uint8_t r26;
	uint8_t r27;
	uint8_t r28;
	uint8_t r29;
	uint8_t r30;
	uint8_t r31;
};

// This is a linked list for the task structs

struct task {
	struct context c;
	void (*task_funct)();
	struct task *next;
	task_state state; 
};

/* First and current structs. 
 * These are used by the ISR in order to
 * work out which task is next.
 */
extern struct task *first;
extern struct task *curr;

/* Set up the current task struct. If prev is not null, then
 * curr will be set as next. In addition, curr's task_funct will
 * point to the function provided. Finally, the pc member of c for
 * curr will point to the address of task_launch.
 *
 * It is assumed that the programmer is smart enough not to 
 * make either curr or task_funct null
 */
void make_task(struct task *prev, struct task *curr, void (*task_funct)());


/* Assign a stack for each task struct. If there are more
 * tasks than stacks, then it will exit with error.
 */

int set_task_stacks(struct task *t, size_t task_num,
			struct stack *s, size_t stack_num);

/* Mark the task as complete. Since the taska aren't
 * actually suppposed to exit, this tells the scheduler
 * not to choose that task, since it's dead.
 */
static inline void end_task(struct task *t) {
	t->state = complete;
}

// run task
static inline void do_task(struct task *t) {
	t->task_funct();
	end_task(t);
	// Infinite loop because we're not supposed to return
	while(1);
}

#endif

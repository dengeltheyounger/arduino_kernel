#ifndef	TASKS_H
#define	TASKS_H
#include <stdlib.h>
#include <stdint.h>
#include "stack.h"
#include <stdio.h>
#include <avr/io.h>

#define	ADDR_LO(LABEL)	LABEL & 0xff
#define	ADDR_HI(LABEL)	(LABEL & 0xff00) >> 8

/* Right now there are only two
 * task states. The only possible
 * reason why this would be necessary
 * is if the programmer had a task
 * that could end, and wanted to use
 * the stack space of that task later.
 */

typedef enum task_state {
	runnable = 0,
	complete = 1,
	waiting = 2
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
	struct task *next;
	task_state state;
	void (*task_funct)(); 
};

extern struct task tasks[];

void make_task(struct task *curr);

/* Assign a stack for each task struct. If there are more
 * tasks than stacks, then it will exit with error.
 */

int set_task_stacks(struct task *t, size_t task_num,
			struct stack *s, size_t stack_num);

/* Mark the task as complete. Since the taska aren't
 * actually suppposed to exit, this tells the scheduler
 * not to choose that task, since it's dead.
 */
void end_task(struct task *t);

// run task
void do_task(struct task *t);

extern struct task *curr;

/* Iterate through the set of tasks to find one that is
 * runnable. If there is no runnable task found, then
 * return false. If a runnable task is found, then save it
 * in curr, and then return true.
 */
unsigned int get_next_task();

#endif

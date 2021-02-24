#ifndef	TASKS_H
#define	TASKS_H
#include <stdlib.h>
#include <stdint.h>
#include "stack.h"
#include <stdio.h>
#include <avr/io.h>

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


// This is a linked list for the task structs

struct task {
	void *stack_start;
	void *stack_ptr;
	struct task *next;
	task_state state;
	void (*task_funct)(); 
};

/* First and current structs. 
 * These are used by the ISR in order to
 * work out which task is next.
 */
extern struct task *first;
extern struct task *curr;
extern struct task *k_task;

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
void end_task(struct task *t);

// run task
void do_task(struct task *t);

#endif

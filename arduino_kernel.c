#include "arduino_kernel.h"

static inline void set_kernel_task(struct task *k) {
	k->state = runnable;
	k->task_funct = check_tasks;
	k_task = k;
}

int kernel_main(uint8_t task_count, 
		void (*task_funct[])(), 
		size_t ssize) {
	// We're not going to tolerate more than 4 tasks for now
	if (task_count > 4)
		return 0;

	int result = 0;
	// Create array of task structs
	struct task tasks[task_count+1];
	// This is the kernel's task struct

	// memset the whole array
	memset(&tasks[0], 0, (task_count+1)*sizeof(struct task));
	// Compiler prefers when we do this
	struct stack s;
	set_kernel_task(&tasks[task_count]);

	// Create linked list
	for (uint8_t i = 0; i < task_count; ++i) {

		if (i == 0)
			make_task(curr, &tasks[i], task_funct[i]);
		else
			make_task(&tasks[i-1], &tasks[i], task_funct[i]);
	}

	// Set first in linked list
	first = &tasks[0];

	// Allocate memory for stack
	char stack_space[(task_count+1)*ssize];
	memset(&stack_space[0],0,(task_count+1)*ssize);

	// Set up task stack region
	s.stack_space = &stack_space[0];
	s.stack_num = task_count;
	s.stack_size = ssize;

	// Set stack pointers for each task
	result = set_task_stacks(&tasks[0], task_count, &s, s.stack_num);

	// If there was an issue with this, exit with error
	if (!result) {
		goto error;
	}

	// Set the timer and then turn on interrupts
	set_timer();

	/* This will turn interrupts off, but at the same time
	 * will jump to the context switch. When the context
	 * switch is finished, it will re-enable interrupts
	 * and move to the next task
	 */
	task_yield();

	/* Now that the timer has been enabled, we wait 
	 * and then switch to first task. 
	 */

	while (1) ;	
	
error:
	return 0;
}

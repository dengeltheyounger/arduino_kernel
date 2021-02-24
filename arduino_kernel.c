#include "arduino_kernel.h"

int kernel_main(uint8_t task_count, 
		void (*task_funct[])(), 
		size_t ssize) {
	// We're not going to tolerate more than 4 tasks for now
	if (task_count > 4)
		return 0;

	int result = 0;
	// Create array of task structs
	struct task tasks[task_count];
	// This is the kernel's task struct
	struct task k;
	k_task = &k;
	// memset the whole array
	memset(&tasks[0], 0, task_count*sizeof(struct task));
	memset(&k, 0, sizeof(struct task));
	// Compiler prefers when we do this
	struct stack s;
	// Now kernel's task struct is considered "first".
	k.c.sp_start = (void *) RAMEND;
	k.state = complete;
	curr = &k;

	// Create linked list
	for (uint8_t i = 0; i < task_count; ++i) {

		if (i == 0)
			make_task(curr, &tasks[i], task_funct[i]);
		else
			make_task(&tasks[i-1], &tasks[i], task_funct[i]);
	}

	// Set first in linked list
	first = &tasks[0];

	// Allocate heap space for a new stack region
	new_stack_space(&s, task_count, ssize);

	// If heap allocation failed, then return with error
	if (!s.stack_space) {
		return 0;
	}

	// Set stack pointers for each task
	result = set_task_stacks(&tasks[0], task_count, &s, s.stack_num);

	// If there was an issue with this, exit with error
	if (!result) {
		release_stacks(&s);
		return 0;
	}

	// Set the timer and then turn on interrupts
	set_timer();
	sei();

	/* Now that the timer has been enabled, we wait 
	 * and then switch to first task. 
	 */
	while (1);
	
	cli();
	release_stacks(&s);
	return 1;
}

#include "arduino_kernel.h"

int kernel_main(uint8_t task_count, 
		void (*task_funct[])(), 
		size_t ssize) {
	// We're not going to tolerate more than 4 tasks for now
	if (task_count > 4)
		return 0;

	int result = 0;
	// Set up kernel's task. It is basically there to move context switcher
	// along
	struct task k;
	k.state = complete;
	k.task_funct = NULL;
	k_task = &k;

	// Create array of task structs
	struct task tasks[task_count];
	// This is the kernel's task struct

	// memset the whole array
	memset(&tasks[0], 0, (task_count)*sizeof(struct task));
	// Compiler prefers when we do this
	struct stack s;
	
	// Create linked list
	for (uint8_t i = 0; i < task_count; ++i) {

		if (i == 0)
			make_task(curr, &tasks[i], task_funct[i]);
		else
			make_task(&tasks[i-1], &tasks[i], task_funct[i]);
	}

	// k_task's next will point to first task in array
	// The last task in array will point to first task in array
	// This will make it easier to keep k_task from running
	k_task->next = &tasks[0];
	tasks[task_count-1].next = &tasks[0];
	curr = k_task;

	// Allocate memory for stack
	unsigned char stack_space[(task_count)*ssize];
	memset(&stack_space[0],0,(task_count)*ssize);

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

	// Set the timer
	set_timer();
	
	/* This will jump to the house keeper. The house keeper will
	 * find a new task and do some house keeping stuff
	 */
	task_yield();

	/* Now that the timer has been enabled, we wait 
	 * and then switch to first task. 
	 */

	while (1) ;	
	
error:
	return 0;
}

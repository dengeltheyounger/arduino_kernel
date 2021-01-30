#include "arduino_kernel.h"

struct task *first = NULL;
struct task *curr = NULL;

int kernel_main(uint8_t task_count, 
		void (*task_funct[])(), 
		size_t ssize) {
	// We're not going to tolerate more than 4 tasks for now
	if (task_count > 4)
		return 0;

#ifdef	DEBUG
	printf("Entered kernel main.\n");
	printf("Number of tasks: %u\n", task_count);
	printf("Size of each stack %u\n", ssize);
	getchar();
#endif

	int result = 0;
	// Create array of task structs
	struct task tasks[task_count];
	// This is the kernel's task struct
	struct task k_task;
	// memset the whole array
	memset(&tasks[0], 0, task_count*sizeof(struct task));
	// Compiler prefers when we do this
	struct stack s;

	// Create linked list
	for (uint8_t i = 0; i < task_count; ++i) {
#ifdef	DEBUG
	printf("Creating new task.\n");
	printf("Index %u, task address %p\n", i, &tasks[i]);
	printf("Address of routine %p\n", task_funct[i]);
	getchar();
#endif
		if (i == 0)
			make_task(NULL, &tasks[i], task_funct[i]);
		else
			make_task(&tasks[i-1], &tasks[i], task_funct[i]);
	}

	// Set first in linked list
	first = &tasks[0];
	// Make a special task struct for the kernel
	make_task(NULL, &k_task, NULL);
	// Have it point to first, and set the inital stack
	k_task.next = first;
	k_task.c.sp_start = (void *) RAMEND;
	/* Now k_task will be the switched out for the first when the interrupt
	 * first triggers.
	 */
	curr = &k_task;
#ifdef	DEBUG
	printf("Set first... Address of first %p\n", first);
	printf("Address of initial task %p\n", &tasks[0]);
	getchar();
#endif

	// Allocate heap space for a new stack region
	new_stack_space(&s, task_count, ssize);
#ifdef	DEBUG
	printf("Allocated stack space.\n");
	getchar();
#endif

	// If heap allocation failed, then return with error
	if (!s.stack_space) {
#ifdef	DEBUG
	printf("Failed to allocate heap space. Exiting\n");
	getchar();
#endif
		return 0;
}

	// Set stack pointers for each task
	result = set_task_stacks(&tasks[0], task_count, &s, s.stack_num);
#ifdef	DEBUG
	printf("Finished set_task_stacks.\n");
	getchar();
#endif

	// If there was an issue with this, exit with error
	if (!result) {
#ifdef	DEBUG
	printf("Error setting stacks. Releasing\n");
	getchar();
#endif
		release_stacks(&s);
		return 0;
	}

	// Set the timer and then turn on interrupts
	set_timer();
	sei();

#ifdef	DEBUG
	printf("Timer enabled... Good luck.\n");
	getchar();
#endif
	/* Now that the timer has been enabled, we wait 
	 * and then switch to first task. 
	 */
	while (1);
#ifdef	DEBUG
	printf("Error! Error!\n");
	getchar();
#endif
	
	release_stacks(&s);
	return 1;
}

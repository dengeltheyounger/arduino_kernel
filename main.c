#include "tasks.h"
#include "timer.h"
#include "system.h"
#include "user.h"
#include "stack.h"
#include "user.h"

// This is mainly declared in case we wish to use flash
extern uint16_t _etext;
extern struct stack s;
extern struct task tasks[TASK_COUNT];

/* Main kernel code. It sets up tasks, stack, sets timer and then goes */

int main() {
	int result = 0;
	// Create linked list
	for (uint8_t i = 1; i < TASK_COUNT; ++i) {

		make_task(&tasks[i-1], &tasks[i], task_funct[i]);
	}

	// Set stack pointers for each task
	result = set_task_stacks(&tasks[0], TASK_COUNT, &s, s.stack_num);

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
	
	/* This should never be reached */
error:
	return 0;
}

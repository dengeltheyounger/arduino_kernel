#include "sys/tasks.h"
#include "tmr/timer.h"
#include "sys/system.h"
#include "user.h"
#include "sys/stack.h"
#include "tmr/software_timer.h"
#include "comm/usart.h"

// This is mainly declared in case we wish to use flash
extern uint16_t _etext;
extern struct stack s;
extern struct task tasks[TASK_COUNT];
extern struct task *curr;


/*!
 *	\brief Initialize the kernel and start the schedule.
 *	Main begins by initializing tasks. After that, it sets their stacks.
 *	Following that, the timers are initialized. After that, control is
 *	given to the scheduler.
 */
int main() {
	int result = 0;
	usart_init();

#if	DEBUG == 1
	println("USART Initialized", SIZEOF("USART Initialized"));
#endif
	// Create linked list
	for (uint8_t i = 0; i < TASK_COUNT; ++i) {
		if (!i) {
			make_task(curr, &tasks[i], task_funct[i]);
			continue;
		}

		make_task(&tasks[i-1], &tasks[i], task_funct[i]);
	}

	tasks[TASK_COUNT-1].next = &tasks[0];

	// Set stack pointers for each task
	result = set_task_stacks(&tasks[0], TASK_COUNT, &s, s.stack_num);

	// If there was an issue with this, exit with error
	if (!result) {
		goto error;
	}


	// Set the timer
	
	init_timers();

	/* This will jump to the house keeper. The house keeper will
	 * find a new task and do some house keeping stuff
	 */
	task_yield();
	
	/* This should never be reached */
error:
	while (1);
}

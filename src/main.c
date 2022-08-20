#include <avr/interrupt.h>
#include "sys/tasks.h"
#include "tmr/timer.h"
#include "sys/system.h"
#include "user.h"
#include "sys/stack.h"
#include "tmr/software_timer.h"
#include "comm/usart.h"
#include "sys/watchdog.h"

// This is mainly declared in case we wish to use flash
extern uint16_t _etext;
extern struct stack s;
extern struct task tasks[TASK_COUNT];

/*
 * This is the kernel task. Right now, it doesn't do anything, but eventually,
 * it can make sure that the tasks are playing nicely with the stacks.
 */
struct task k = {
	.c = {0},
	.state = complete,
	.task_funct = NULL,
	.next = &tasks[0]
};

/*
 * This is a pointer to the current task. Initially, it is set to the kernel
 * task (k).
 */
struct task *curr = &k;

/*!
 *	\brief Initialize the kernel and start the schedule.
 *	Main begins by initializing tasks. After that, it sets their stacks.
 *	Following that, the timers are initialized. After that, control is
 *	given to the scheduler.
 */

ISR(BADISR_vect) {
	println("Default ISR called!", STRLEN("Default ISR called!"));
	while (1);
}

int main() {
	int result = 0;
	usart_init();

#if	DEBUG == 1
	println("USART Initialized", STRLEN("USART Initialized"));
#endif
	// Create linked list
	for (uint8_t i = 0; i < TASK_COUNT; ++i) {
		make_task(&tasks[i]);
	}

	// Set stack pointers for each task
	result = set_task_stacks(&tasks[0], TASK_COUNT, &s, s.stack_num);

	// If there was an issue with this, exit with error
	if (!result) {
		goto error;
	}


	// Set the timer

#if	DEBUG == 1
	println("Timer initialization started", 
		STRLEN("Timer initialization started"));
#endif

	init_timers();

#if	DEBUG == 1
	println("Timer initialization stopped",
		STRLEN("Timer initialization stopped"));
#endif

	/* This will jump to the house keeper. The house keeper will
	 * find a new task and do some house keeping stuff
	 */

#if	DEBUG == 1
	println("Scheduler starting. Best of luck!", 
		STRLEN("Scheduler starting. Best of luck!"));
#endif
	task_yield();
	
	/* This should never be reached */
error:

#if	DEBUG == 1
	println("Entered the error state. Something went wrong.",
		STRLEN("Entered the error state. Something went wrong."));
#endif
	while (1);
}

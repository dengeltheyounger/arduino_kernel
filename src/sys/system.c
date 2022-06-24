#include "sys/system.h"

volatile struct sys_clock system_time = { .time = 0 };

/*!
 *	\brief Put a task to sleep for a certain period of time.
 *	The sleep time is added onto the system time to give a certain wake up
 *	time. This can probably be optimized, and make more stable.
 *
 *	\param task_ndx
 *	The index of the task
 *
 *	\param time
 *	The total length of time that the task will sleep.
 */
void task_sleep(uint8_t task_ndx, uint32_t time) {
	/* Make an entry for the current task */
	add_req_entry(task_ndx, system_time.time+time);

	curr->state = waiting;

	task_yield();
}

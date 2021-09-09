#include "system.h"

volatile struct sys_clock system_time = { .time = 0 };

void task_sleep(uint32_t time) {
	/* Make an entry for the current task */
	add_req_entry(curr, system_time.time+time);

	curr->state = waiting;

	task_yield();
}

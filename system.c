#include "system.h"

extern void do_housekeeping();

void task_yield() {
	do_housekeeping
}

int task_sleep(uint32_t time) {
	/* Make an entry for the current task */
	int result = make_list_entry(curr, system_time.time+time);

	if (!result) {
		return 0;
	}

	curr->state = waiting;

	task_yield();

	return 1;
}

#include "housekeeper_utilities.h"

extern unsigned char task_unavailable;

void check_wait_list() {
	/* See if there's a task to take off of the wait list */
	if (head->value <= system_time.time) {
		remove_entry_top();
	}
}

void get_new_task() {

	/* Create a temporary label to store next task to be visited */
	
	struct task *tmp = curr;

	curr = curr->next;

	do {
		/* Go through each task to find a runnable task.
		 * If it's not runnable, go to next task
		 *
		 * If we have a runnable task, then set task_unavailable
		 * flag down and then exit. Curr should be set to the
		 * next task
		 */
		if (curr->state != runnable) {
			curr = curr->next;
		}

		else {
			// indicate that we have a valid task
			task_unavailable = 0;
			// Exit because we have our task now
			return;
		}
	} while (tmp != curr);

	/* We do not have an available task. Go to next part of housekeeper */ 
	task_unavailable = 1;
}


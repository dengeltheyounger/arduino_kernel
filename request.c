#include "request.h"

void add_req_entry(struct task *t, uint32_t value) {
	/* iterate through the list of request entries
	 * until one is found that is either greater than the
	 * desired wakeup time of t, or inactive.
	 */
	for (uint16_t i = 0; i < request_max; ++i) {
		/* If we find a task with inactive status,
		 * then we're going to simply store the
		 * time information there
		 */
		if (req_head[i].status == inactive) {
			req_head[i].value = value;
			req_head[i].t = t;
			req_head[i].status = active;
			break;
		}

		if (req_head[i].value > value) {
			/* Once this is found, shift the structs towards 
			 * the back, starting from where the desired wake
			 * up time is greater.
			 */
			for (uint16_t j = request_max; j > i; --j) {
				req_head[j-1].value = req_head[j-2].value;
				req_head[j-1].t = req_head[j-2].t;
				req_head[j-1].status = req_head[j-2].status;
			}

			/* Put the new request in where the starting position
			 * of the shift is located
			 */
			req_head[i].value = value;
			req_head[i].t = t;
			req_head[i].status = active;
			break;
		}
	}
}

void check_req_top() {
	/* If we have gotten to the desired wakeup time,
	 * Then remove the entry. Double check that a request has
	 * been made in the first place
	 * Otherwise, just return
	 */
	if (system_time.time >= req_head[0].value && 
				req_head[0].status == active) {

		/* Ideally, something else would be changing the status
		 * of the task. However, this is an embedded system, 
		 * and so I'm going to go ahead and do it here.
		 */
		// Set task to runnable
		req_head[0].t->state = runnable;

		for (uint16_t i = 1; i < request_max; ++i) {

			req_head[i-1].value = req_head[i].value;
			req_head[i-1].t = req_head[i].t;
			req_head[i-1].status = req_head[i].status;
			/* This should ensure that the first inactive entry
			 * is copied into the next position
			 */
			if (req_head[i].status == inactive) {
				break;
			}
			
			/* This handles the case where there all entries were active,
			 * but we removed the top. Now we have ensured that the last
			 * index is empty (inactive).
			 * 
			 * The next time we remove an entry, the last index will be
			 * copied into the one before it.
			 */
			if (i == request_max - 1) {
				req_head[i].status = inactive;
			}
		}
	}
}


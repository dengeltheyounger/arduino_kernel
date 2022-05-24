#include "sys/request.h"

void add_req_entry(uint8_t task_ndx, uint32_t value) {
	uint8_t task_tmp = 0;

	/* Go through the array of requests and determine
	 * where the value of one is greater than the new
	 * value. This means that the new sleeper will
	 * wake up before the sleeper in the array element
	 */
	for (uint8_t i = 0; i < REQUEST_MAX; ++i) {
		task_tmp = request_array[i];

		/* If there's an empty spot, go ahead and add */
		
		if (request_array[i] == -1) {
			request_array[i] = task_ndx;
		}
		/* If a later sleeper is found, then shift all of the
		 * elements of the array to the right by 1. This will
		 * make room for the new sleeper between the earlier
		 * wake up time and later wake up time.
		 */
		else if (requests[task_tmp].value > value) {
			for (uint8_t j = REQUEST_MAX - 1; j > i; --j) {
				request_array[j] = request_array[j-1];
			}
			
		}

		/* This is to avoid repeating two lines of code */
		else {
			continue;
		}

		/* Add new sleeper */
		requests[task_ndx].value = value;
		request_array[i] = task_ndx;
		break;

	}
}

void check_req_top() {
	int wakers_found = 1;
	uint8_t task_ndx = 0;

	/* If nothing's in the array, then just exit */
	if (request_array[0] == -1)
		return;

	/* Unblock all tasks need to be woken up */

	while (wakers_found) {
		task_ndx = request_array[0];

		/* If the task can be woken up, then go through and
		 * shift all of the indices by one. If a -1 is found
		 * before that point, then exit.
		 * If we got to the end, but there were no -1's found,
		 * then set the last index to -1
		 */
		if (system_time.time >= requests[task_ndx].value) {

			/* Wake the task back up. Ideally, this should
			 * be done somewhere else, but right now it's
			 * good.
			 */
			tasks[task_ndx].state = runnable;

			for (uint8_t i = 0; i < REQUEST_MAX - 1; ++i) {
				if (request_array[i] != -1)
					request_array[i] = request_array[i+1];
				else {
					request_array[i-1] = -1;
					break;
				}
			}

			request_array[REQUEST_MAX-1] = -1;
		}

		else {
			wakers_found = 0;
		}

	}
}


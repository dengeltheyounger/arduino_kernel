#include <avr/interrupt.h>
#include "user.h"
#include "tmr/software_timer.h"

extern volatile struct sys_clock system_time;

extern volatile struct software_timer tmr_arr[];

volatile struct software_timer *tmr_arr_ptr[ SOFTWARE_TIMER_COUNT ];

volatile uint8_t software_timer_iteration = 0;

volatile struct queue tmr_callback_queue = {
	.queue_size = SOFTWARE_TIMER_COUNT,
	.head = 0,
	.tail = 0,
	.items = { [0 ... SOFTWARE_TIMER_COUNT - 1] = 0 }
};

void init_software_timers() {
	uint8_t back = SOFTWARE_TIMER_COUNT - 1;
	uint8_t front = 0;

	for (uint8_t i = 0; i < SOFTWARE_TIMER_COUNT; ++i) {
		if (tmr_arr[i].state == timer_started) {
			tmr_arr_ptr[front++] = &tmr_arr[i];
		}

		else if (tmr_arr[i].state == timer_stopped) {
			tmr_arr_ptr[back--] = &tmr_arr[i];
		}

	}
}

void timer_start(struct software_timer *tmr) {
	struct software_timer *tmr_tmp = NULL;
	uint8_t i = 0;
	uint8_t j = 0;

	for (i = 0; i < SOFTWARE_TIMER_COUNT; ++i) {
		if (tmr_arr_ptr[i]->state == timer_stopped) {
			break;
		}
	}
	
	for (j = i+1; j < SOFTWARE_TIMER_COUNT; ++j) {
		if (tmr_arr_ptr[j]->id == tmr->id) {
			tmr_tmp = tmr_arr_ptr[i];
			tmr_arr_ptr[i] = tmr_arr_ptr[j];
			tmr_arr_ptr[j] = tmr_tmp;
			tmr->state = timer_started;
			tmr->counter = 0;
		}
	}
}

void timer_stop(struct software_timer *tmr) {
	struct software_timer *tmr_tmp = NULL;
	uint8_t i = 0;
	uint8_t j = 0;

	for (i = 0; i < SOFTWARE_TIMER_COUNT; ++i) {
		if (tmr_arr_ptr[i]->id == tmr->id) {
			break;
		}
	}

	for (j = i+1; j < SOFTWARE_TIMER_COUNT; ++j) {
		if (tmr_arr_ptr[j]->state == timer_stopped) {
			tmr_tmp = tmr_arr_ptr[i];
			tmr_arr_ptr[i] = tmr_arr_ptr[j-1];
			tmr_arr_ptr[j] = tmr_tmp;
			tmr->state = timer_stopped;
		}
	}
}

/* If we've reached the millisecond mark, then run through the timers. If a 
 * timer is stoppped, then exit the loop, because all of the rest are stopped.
 * For each timer that is not stopped, decrement its counter. If the counter is
 * at zero, then add it to the queue of callbacks.
 *
 * Attempt to get a callback from the queue, and then run a callback. The ISR
 * can do this at most five times within a millisecond, which means that you
 * have to be careful about the time length of the callback as well as the
 * number of 1 ms software timers (and the number of timers in general).
 */
ISR(TIMER0_COMPA_vect) {

	void (*callback)();

	if (++software_timer_iteration % SOFTWARE_TIMER_COUNT == 0) {
			
		for (uint8_t i = 0; i < SOFTWARE_TIMER_COUNT; ++i) {
			if (tmr_arr_ptr[i]->state == timer_stopped) {
				break;
			}

			tmr_arr_ptr[i]->counter--;

			if (tmr_arr_ptr[i]->counter == 0) {
				enqueue(&tmr_callback_queue, 
					(void *) tmr_arr_ptr[i]->callback);
			}
		}
	}

	callback = dequeue(&tmr_callback_queue);

	if (callback != NULL) {
		callback();
	}
}

#include <avr/interrupt.h>
#include <string.h>
#include "user.h"
#include "tmr/software_timer.h"
#include "comm/usart.h"
#if USE_SOFTWARE_TIMER == 1

#define	SOFTWARE_TIMER_ITERATIONS	5

extern volatile struct sys_clock system_time;

extern volatile struct software_timer tmr_arr[];

volatile struct software_timer *tmr_arr_ptr[ SOFTWARE_TIMER_COUNT ];

volatile uint8_t software_timer_iteration = 0;

volatile struct queue tmr_callback_queue = {
	.capacity = SOFTWARE_TIMER_COUNT,
	.size = 0,
	.head = 0,
	.tail = 0,
	.items = { [0 ... SOFTWARE_TIMER_COUNT - 1] = 0 }
};

/*
 * Initialize the timers by putting the stopped timers in the back and the
 * started timers in the front. For each started timer, set the counter to the
 * period.
 */
void init_software_timers() {
	uint8_t back = SOFTWARE_TIMER_COUNT - 1;
	uint8_t front = 0;

#if DEBUG == 1
	println_c("Entered software timer initializer");
#endif
	for (uint8_t i = 0; i < SOFTWARE_TIMER_COUNT; ++i) {
		if (tmr_arr[i].state == timer_started) {
			tmr_arr[i].counter = tmr_arr[i].period;
			tmr_arr_ptr[front++] = &tmr_arr[i];
#if	DEBUG == 1
			println_c("Timer added to next position");
#endif
		}

		else if (tmr_arr[i].state == timer_stopped) {
			tmr_arr_ptr[back--] = &tmr_arr[i];
#if	DEBUG == 1
			println_c("Timer added to last available position");
#endif
		}

		else {
#if	DEBUG == 1
			println_c("Reached else... continuing");
#endif
			continue;
		}

	}

#if	DEBUG == 1
	println_c("Exiting software timer initializer");
#endif
}

/*
 * When starting a timer, figure out where the first stopped timer is at.
 * After that, continue searching for the timer to be started. Swap them
 * if the timer to be started is found in the list of stopped timers.
 * Initialize the started timer with the counter being equal to the period.
 */
void software_timer_start(volatile struct software_timer *tmr) {
	struct software_timer *tmr_tmp = NULL;
	uint8_t i = 0;
	uint8_t j = 0;

#if	DEBUG == 1
	println_c("Entered software timer start");
#endif
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
			tmr->counter = tmr->period;
		}
	}

#if	DEBUG == 1
	println_c("Exited software timer start");
#endif
}

/*
 * Find the position of the timer to stop. After that, determine whether or not
 * we reached the end of the software timers. If we found a timer, then i 
 * should be less than the total number of software timers. If so, then we
 * memmove the remaining timers, and then throw the software timer being
 * stopped in the back.
 */
void software_timer_stop(volatile struct software_timer *tmr) {
	struct software_timer *tmr_tmp = NULL;
	uint8_t i = 0;
	uint8_t j = 0;
	uint8_t timers_remaining = 0;

#if	DEBUG == 1
	println_c("Entered software timer stop");
#endif

	for (i = 0; i < SOFTWARE_TIMER_COUNT; ++i) {
		if (tmr_arr_ptr[i]->id == tmr->id) {
			break;
		}
	}
		
	if (i != SOFTWARE_TIMER_COUNT) {
		timers_remaining = SOFTWARE_TIMER_COUNT - i + 1;
		memmove(&tmr_arr_ptr[i], &tmr_arr_ptr[i+1], timers_remaining);
		tmr_arr_ptr[SOFTWARE_TIMER_COUNT - 1] = tmr;
	}

#if 	DEBUG == 1
	println_c("Exited software timer stop");
#endif
}

/* If we've reached the millisecond mark, then run through the timers. If a 
 * timer is stoppped, then exit the loop, because all of the rest are stopped.
 * For each timer that is not stopped, decrement its counter. If the counter is
 * at zero, then add it to the queue of callbacks. If it is a periodic timer,
 * then reload the timer.
 *
 * Attempt to get a callback from the queue, and then run a callback. The ISR
 * can do this at most five times within a millisecond, which means that you
 * have to be careful about the time length of the callback as well as the
 * number of 1 ms software timers (and the number of timers in general).
 */
ISR(TIMER0_COMPA_vect) {

	void (*callback)();

	software_timer_iteration = ++software_timer_iteration % 
		SOFTWARE_TIMER_ITERATIONS;

	if (software_timer_iteration == 0) {
			
		for (uint8_t i = 0; i < SOFTWARE_TIMER_COUNT; ++i) {
			if (tmr_arr_ptr[i]->state == timer_stopped) {
				break;
			}

			tmr_arr_ptr[i]->counter--;

			if (tmr_arr_ptr[i]->counter == 0) {

				if (tmr_arr_ptr[i]->t == 
					sw_timer_periodic) {

					tmr_arr_ptr[i]->counter = 
						tmr_arr_ptr[i]->period;
				}

				if (queue_is_full_from_isr(&tmr_callback_queue)) 
				{

					break;
				}

				enqueue_from_isr(&tmr_callback_queue, 
					tmr_arr_ptr[i]->callback);
			}
		}
	}


	callback = dequeue_from_isr(&tmr_callback_queue);

	if (callback) {
		callback();
	}
}

#endif

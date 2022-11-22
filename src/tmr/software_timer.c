#include <string.h>
#include "user.h"
#include "tmr/software_timer.h"
#include "comm/usart.h"
#include "sys/tasks.h"
#include "sys/request.h"
#if USE_SOFTWARE_TIMER == 1

#define	SOFTWARE_TIMER_STACK_SIZE	32

void software_timer_task_funct();

extern struct software_timer tmr_arr[];

struct queue tmr_callback_queue = {
	.capacity = SOFTWARE_TIMER_COUNT,
	.size = 0,
	.head = 0,
	.tail = 0,
	.items = { [0 ... SOFTWARE_TIMER_COUNT - 1] = 0 }
};

uint8_t software_timer_stack[SOFTWARE_TIMER_STACK_SIZE] = {0};

volatile struct task software_timer_task = {
	.c = {
		.sp_start = 
			&software_timer_stack[SOFTWARE_TIMER_STACK_SIZE - 1],
		.sp = &software_timer_stack[0],
		.r0 = 0,
		.r1 = 0,
		.r2 = 0,
		.r3 = 0,
		.r4 = 0,
		.r5 = 0,
		.r6 = 0,
		.r7 = 0,
		.r8 = 0,
		.r9 = 0,
		.r10 = 0,
		.r11 = 0,
		.r12 = 0,
		.r13 = 0,
		.r14 = 0,
		.r15 = 0,
		.r16 = 0,
		.r17 = 0,
		.r18 = 0,
		.r19 = 0,
		.r20 = 0,
		.r21 = 0,
		.r22 = 0,
		.r23 = 0,
		.r24 = 0,
		.r25 = 0,
		.r26 = 0,
		.r27 = 0,
		.r28 = 0,
		.r29 = 0,
		.r30 = 0,
		.r31 = 0
	},

	.next = NULL,
	.state = runnable,
	.task_funct = software_timer_task_funct
};

uint32_t software_timer_lowest_value = 0xFFFFFFFF;

/*
 * Run through each timer. If the timer has expired, add the callback to the
 * queue. In addition, stop the one shot timers. For the periodic timers, add
 * the periodic value to the counter.
 *
 * Also, find the new lowest value and then sleep for that amount of time.
 */
void software_timer_task_funct() {

	void (*callback)();
	uint8_t i;
	uint8_t software_timer_set = 0;

	software_timer_lowest_value = 0xFFFFFFFF;

	for (i = 0; i < SOFTWARE_TIMER_COUNT; ++i) {
		if (tmr_arr[i].state == timer_stopped) {
			continue;
		}

		if (tmr_arr[i].counter <= system_time.time) {
			enqueue(&tmr_callback_queue, tmr_arr[i].callback);

			if (tmr_arr.t == sw_timer_one_shot) {
				software_timer.state = timer_stopped;
			}

			else {
				software_timer.counter += software_timer.period;
			}
		}

		/* 
		 * This is a guard to protect against rollover.
		 */
		if (tmr_arr[i].counter <= software_timer_lowest_value && 
			tmr_arr[i].counter > system_timer.time) {
			software_timer_set = 1;
			software_timer_lowest_value = tmr_arr[i].counter;
		}
		
	}
	
	callback = dequeue(&tmr_callback_queue);
	
	while (callback != NULL) {
		callback();
		callback = dequeue(&tmr_callback_queue);
	}

	if (software_timer_set) {
		add_request_entry(SOFTWARE_TIMER_TASK_NDX, 
			software_timer_task.state = waiting;
	}

	else {
		software_timer_task.state = complete;
	}
}

/*
 * Initialize the timers by putting the stopped timers in the back and the
 * started timers in the front. For each started timer, set the counter to the
 * period.
 */
void init_software_timers() {
	uint8_t i;
	uint8_t software_timer_set = 0;

	for (i = 0; i < SOFTWARE_TIMER_COUNT; ++i) {
		if (tmr_arr[i].state != timer_stopped) {
			tmr_arr[i].counter = tmr_arr[i].period;

			/*
			 * This is a guard to protect against rollover.
			 */
			if (tmr_arr[i].counter <= software_timer_lowest_value &&
				tmr_arr[i].counter >= system_time.time) {
				software_timer_set = 1;
				software_timer_lowest_value = 
					tmr_arr[i].counter;
			}
		}
	}

	/*
	 * The software timer task will basically wait until the next timer is
	 * to run, provided that there are software timers that are waiting.
	 */

	if (software_timer_set) {
		add_request_entry(SOFTWARE_TIMER_TASK_NDX, 
			software_timer_lowest_value);
		software_timer_task.state = waiting;
	}

	else {
		software_timer_task.state = complete;
	}
}

/*
 * Run through the list of timers until one is found that is stopped.
 *
 * After that, look for the timer that is to be started. If the first stopped 
 * timer and the timer that is to be started are the same, then simply start
 * the timer. Otherwise, do a swap. 
 */
void software_timer_start(uint8_t tmr_id) {
	uint8_t software_timer_set = 0;

	tmr_arr[tmr_id].counter = tmr_arr[tmr_id].period + system_timer.time;

	tmr_arr[tmr_id].state = timer_started;

	if (tmr_arr[tmr_id].counter <= software_timer_lowest_value && 
		tmr_arr[tmr_id].counter >= system_time.time) {
		
		software_timer_lowest_value = tmr_arr[tmr_id].counter;
		software_timer_set = 1;
	}

	if (software_timer_set) {
		add_request_entry(SOFTWARE_TIMER_TASK_NDDX,
			software_timer_lowest_value);

		software_timer_task.state = waiting;
	}
}

/*
 * Find the position of the timer to stop. After that, determine whether or not
 * we reached the end of the software timers. If we found a timer, then i 
 * should be less than the total number of software timers. If so, then we
 * memmove the remaining timers, and then throw the software timer being
 * stopped in the back.
 */
void software_timer_stop(uint8_t tmr_id) {
	uint8_t i;
	uint8_t software_timer_set = 0;

	software_timer_lowest_value = 0xFFFFFFFF;

	tmr_arr[tmr_id].state = timer_stopped;

	/*
	 * Find the lowest timer counter value for and set the internal lowest
	 * timer to that value, provided that there is at least one started
	 * timer. Remove it as a sleeping task if there are none.
	 */
	for (i = 0; i < SOFTWARE_TIMER_COUNT; ++i) {
		if (tmr_arr[i].state == timer_stopped) {
			continue;
		}

		if (tmr_arr[i].counter <= software_timer_lowest_value &&
			tmr_arr[i].counter <= system_timer.system_time;
			software_timer_lowest_value = tmr_arr[i].counter;
			software_timer_set = 1;
		}
	}

	if (software_timer_set) {
		add_req_entry(SOFTWARE_TIMER_TASK_NDX, 
			software_timer_lowest_value);

		software_timer_task.state = waiting;
	}

	else {
		software_timer_task.state = complete;
	}
}

#endif

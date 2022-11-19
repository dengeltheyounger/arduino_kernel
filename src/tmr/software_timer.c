#include <avr/interrupt.h>
#include <string.h>
#include "user.h"
#include "tmr/software_timer.h"
#include "comm/usart.h"
#include "sys/tasks.h"
#if USE_SOFTWARE_TIMER == 1

#define	SOFTWARE_TIMER_STACK_SIZE	32

void software_timer_task_funct();

extern struct software_timer tmr_arr[];

struct software_timer *tmr_arr_ptr[SOFTWARE_TIMER_COUNT];

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

/*
 * Run through each of the timers until we either get to the end, or we get to 
 * a timer that is stopped.
 *
 * Decrement the counter of timer. If the timer's counter is 0, then enqueue
 * it. Afterwards, reset it.
 *
 * If we successfully dequeued a timer callback, then run it.
 */
void software_timer_task_funct() {
	void (*callback)();

	for (uint8_t i = 0; i < SOFTWARE_TIMER_COUNT; ++i) {
		if ((*tmr_arr_ptr[i]).state == timer_stopped) {
			break;
		}

		if (((*tmr_arr_ptr[i]).counter--) == 0) {
			enqueue(&tmr_callback_queue, 
				(*tmr_arr_ptr[i]).callback);
			(*tmr_arr_ptr[i]).counter = (*tmr_arr_ptr[i]).period;
		}

	}
	
	callback = dequeue(&tmr_callback_queue);
	
	while (callback != NULL) {
		callback();
		callback = dequeue(&tmr_callback_queue);
	}
}

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
 * Run through the list of timers until one is found that is stopped.
 *
 * After that, look for the timer that is to be started. If the first stopped 
 * timer and the timer that is to be started are the same, then simply start
 * the timer. Otherwise, do a swap. 
 */
void software_timer_start(struct software_timer *tmr) {
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
	
	for (j = i; j < SOFTWARE_TIMER_COUNT; ++j) {
		if (tmr_arr_ptr[j]->id == tmr->id) {
			if (j != i) {
				tmr_tmp = tmr_arr_ptr[i];
				tmr_arr_ptr[i] = tmr_arr_ptr[j];
				tmr_arr_ptr[j] = tmr_tmp;
			}
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
void software_timer_stop(struct software_timer *tmr) {
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

#endif

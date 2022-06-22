#include "tmr/software_timer.h"

extern volatile struct software_timer tmr_arr[];

extern volatile uint8_t tmr_arr_size;

volatile struct software_timer *tmr_arr_ptr[tmr_arr_size];

volatile uint8_t time_counter = 0;

volatile struct queue tmr_callback_queue = {
	.queue_size = tmr_arr_size,
	.head = 0,
	.tail = 0,
	.items = { [0 ... tmr_arr_size] = 0 };
};

void init_software_timers() {
	uint8_t back = tmr_arr_size - 1;
	uint8_t front = 0;

	for (uint8_t i = 0; i < tmr_arr_size; ++i) {
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

	for (i = 0; i < tmr_arr_size; ++i) {
		if (tmr_arr_ptr[i]->state == timer_stopped) {
			break;
		}
	}
	
	for (j = i+1; j < tmr_arr_size; ++j) {
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

	for (i = 0; i < tmr_arr_size; ++i) {
		if (tmr_arr_ptr[i]->id == tmr->id) {
			break;
		}
	}

	for (j = i+1; j < tmr_arr_size; ++j) {
		if (tmr_arr_ptr[j]->state == timer_stopped) {
			tmr_tmp = tmr_arr_ptr[i];
			tmr_arr_ptr[i] = tmr_arr_ptr[j-1];
			tmr_arr_ptr[j] = tmr_tmp;
			tmr->state = timer_stopped;
		}
	}
}


		

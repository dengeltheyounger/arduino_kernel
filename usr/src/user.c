#include "user.h"

// User must define task funct array here

#define	NOP()	asm("nop\n\t")

void main_task() {

	DDRB |= (1 << 0);
	DDRB |= (1 << 1);
	DDRB |= (1 << 2);

	PORTB |= (1 << 2);

	task_sleep(0, 1000);

	software_timer_start(&tmr_arr[1]);

	while (1) {
	
		PORTB &= ~(1 << 2);

		task_sleep(0,250);

		PORTB |= (1 << 2);

		task_sleep(0,250);
	}
};

void second_task() {
	while (1) {
		task_sleep(1, 250);
	}
}

void third_task() {
	while (1) {
		task_sleep(2, 500);
	}
}

struct task tasks[TASK_COUNT] = {
	[0] = {
		.c = {0},
		.next = &tasks[1],
		.state = runnable,
		.task_funct = main_task
	},

	[1] = {
		.c = {0},
		.next = &tasks[0],
		.state = runnable,
		.task_funct = second_task
	},/*

	[2] = {
		.c = {0},
		.next = &tasks[0],
		.state = runnable,
		.task_funct = third_task
	}*/
};

uint8_t stack_space[TASK_COUNT*STACK_SIZE] = {0};

struct stack s = { 
	.stack_space = &stack_space[0],
	.stack_num = TASK_COUNT,
	.stack_size = STACK_SIZE
};

struct request_entry requests[REQUEST_MAX] = {0};

int request_array[REQUEST_MAX] = { [0 ... REQUEST_MAX-1] = -1};

#if USE_SOFTWARE_TIMER == 1

enum led_state {
	LED_ON,
	LED_OFF
};

uint8_t led1_state = LED_OFF;

uint8_t led2_state = LED_ON;

void switch_led1() {
	if (led1_state == LED_OFF) {
		PORTB |= (1 << 0);
		led1_state = LED_ON;
	}

	else {
		PORTB &= ~(1 << 0);
		led1_state = LED_OFF;
	}
}

void switch_led2() {
	if (led2_state == LED_OFF) {
		PORTB |= (1 << 1);
		led2_state = LED_ON;
	}

	else {
		PORTB &= ~(1 << 1);
		led2_state = LED_OFF;
	}
}

struct software_timer tmr_arr[SOFTWARE_TIMER_COUNT] = {
	
	[0] = {
		.id = 0,
		.period = 500,
		.counter = 0,
		.state = timer_started,
		.t = sw_timer_periodic,
		.callback = switch_led1
	},

	[1] = {
		.id = 1,
		.period = 500,
		.counter = 0,
		.state = timer_stopped,
		.t = sw_timer_periodic,
		.callback = switch_led2
	}
};

#endif



#include "user.h"

// User must define task funct array here

#define	NOP()	asm("nop\n\t")

void main_task() {
#if	DEBUG == 1
		println("Entered main task", 
			STRLEN("Entered main task"));
#endif

	DDRB |= (1 << 0);
	DDRB |= (1 << 1);

	while (1) {
#if	DEBUG == 1
		println("Entering task sleep - main task", 
			STRLEN("Entering task sleep - main task"));
#endif

		task_sleep(0,1000);

#if 	DEBUG == 1
		println("Exiting task sleep - main task",
			STRLEN("Exiting task sleep - main task"));
	}
#endif
};

struct task tasks[TASK_COUNT] = {
	[0] = {
		.c = {0},
		.next = &tasks[0],
		.state = runnable,
		.task_funct = main_task
	}
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

volatile struct software_timer tmr_arr[SOFTWARE_TIMER_COUNT] = {
	
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
		.state = timer_started,
		.t = sw_timer_periodic,
		.callback = switch_led2
	}
};

#endif



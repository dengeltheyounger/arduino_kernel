#include "user.h"

// User must define task funct array here

#define	NOP()	asm("nop\n\t")

void main_task() {
#if	DEBUG == 1
		println("Entered main task", 
			STRLEN("Entered main task"));
#endif
	while (1) {
#if	DEBUG == 1
		println("Entering task sleep - main task", 
			STRLEN("Entering task sleep - main task"));
#endif

		task_sleep(0,10);

#if 	DEBUG == 1
		println("Exiting task sleep - main task",
			STRLEN("Exiting task sleep - main task"));
	}
#endif
};

void led_blink_1() {
	DDRB |= (1 << 0);
	while(1) {
		PORTB &= ~(1 << 0);
		task_sleep(1,500);
		PORTB |= (1 << 0);
		task_sleep(1,500);
	}
}

void led_blink_2() {
	DDRB |= (1 << 1);
	while(1) {
		PORTB |= (1 << 1);
		task_sleep(2,500);
		PORTB &= ~(1 << 1);
		task_sleep(2,500);
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
		.next = &tasks[2],
		.state = runnable,
		.task_funct = led_blink_1
	},

	[2] = {
		.c = {0},
		.next = &tasks[0],
		.state = runnable,
		.task_funct = led_blink_2
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

volatile struct software_timer tmr_arr[SOFTWARE_TIMER_COUNT] = {
	/*[0] = {
		.id = 0,
		.period = 1000,
		.counter = 0,
		.state = timer_stopped,
		.t = sw_timer_periodic,
		.callback = DHCP_time_handler
	},*/

	[0] = {
		.id = 0,
		.period = 5000,
		.counter = 0,
		.state = timer_stopped,
		.t = sw_timer_periodic,
		.callback = do_ethernet_send
	}
};

#endif



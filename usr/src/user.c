#include "user.h"

// User must define task funct array here

#define	NOP()	asm("nop\n\t")

void main_task() {
	//software_timer_start(&tmr_arr[0]);
	task_sleep(0,5);
	//software_timer_stop(&tmr_arr[0]);
	task_sleep(0,10);
	//software_timer_start(&tmr_arr[0]);
	task_sleep(0,5);
	//software_timer_stop(&tmr_arr[1]);
	//software_timer_start(&tmr_arr[3]);
};

void (*task_funct[TASK_COUNT])() = {
	main_task
};

struct task tasks[TASK_COUNT] = {
	[0] = {
		.c = {0},
		.next = &tasks[0],
		.state = runnable,
		.task_funct = main_task
	}
};
struct task k = { 
			.c = {0},
			.state = complete,
			.task_funct = NULL
		};

struct task *curr = &k;

uint8_t stack_space[TASK_COUNT*STACK_SIZE] = {0};

struct stack s = { 
		.stack_space = &stack_space[0],
		.stack_num = TASK_COUNT,
		.stack_size = STACK_SIZE
		};

struct request_entry requests[REQUEST_MAX] = {0};

int request_array[REQUEST_MAX] = { [0 ... REQUEST_MAX-1] = -1};

#if USE_SOFTWARE_TIMER == 1

void timer0_callback() {
	NOP();
}

void timer1_callback() {
	NOP();
}

void timer2_callback() {
	NOP();
}

void timer3_callback() {
	NOP();
}

void timer4_callback() {
	NOP();
}

volatile struct software_timer tmr_arr[ SOFTWARE_TIMER_COUNT ] = {
	[0] = {
		.id = 0,
		.period = 100,
		.counter = 0,
		.state = timer_stopped,
		.callback = timer0_callback
	},

	[1] = {
		.id = 1,
		.period = 1,
		.counter = 0,
		.state = timer_started,
		.callback = timer1_callback
	},

	[2] = {
		.id = 2,
		.period = 500,
		.counter = 0,
		.state = timer_started,
		.callback = timer2_callback,
	},

	[3] = {
		.id = 3,
		.period = 1,
		.counter = 0,
		.state = timer_stopped,
		.callback = timer3_callback
	},

	[4] = {
		.id = 4,
		.period = 2,
		.counter = 0,
		.state = timer_started,
		.callback = timer4_callback
	}
};

#endif

#if USE_ETHERNET == 1
struct ethernet_controller usr_eth_ctrl = {
	.mac_address = {
		0xA8, 0x61, 0x0A, 0xAE, 0xAA, 0x2C 
	},
	.ip_address = {
		192, 168, 10, 250
	},

	.init_ethernet = init_w5500_eth_ctrl,
	.deinit_ethernet = deinit_w5500_eth_ctrl
};

struct ethernet_handle usr_eth_handle = {
	.open_socket = w5500_open_socket,
	.send_packet = w5500_send_packet,
	.receive_packet = w5500_receive_packet,
	.close_socket = w5500_close_socket,
	.s = {
		.socket_num = SOCKET_UNALLOCATED,
		.protocol = UDP,
		.state = SOCKET_CLOSED
	}
};
#endif



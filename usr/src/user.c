#include "user.h"

// User must define task funct array here

void (*task_funct[TASK_COUNT])() = {
					blink1,
					blink2,
					blink3,
					blink4
				};

struct task tasks[TASK_COUNT] = {0};
struct task k = { 
			.c = {0},
			.state = complete,
			.task_funct = NULL
		};

struct task *curr = &k;

volatile struct software_timer tmr_arr[] = {

};

volatile uint8_t tmr_arr_size = 0;

uint8_t stack_space[TASK_COUNT*STACK_SIZE] = {0};

struct stack s = { 
		.stack_space = &stack_space[0],
		.stack_num = TASK_COUNT,
		.stack_size = STACK_SIZE
		};

struct request_entry requests[REQUEST_MAX] = {0};

int request_array[REQUEST_MAX] = { [0 ... REQUEST_MAX-1] = -1};

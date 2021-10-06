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
			.next = &tasks[0],
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

struct request_entry req_entries[REQUEST_MAX] = {0};
struct request_entry *req_head = &req_entries[0];



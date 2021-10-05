#include "user.h"

/* Task structs defined here.
 * Leave k_task alone, define array of 
 * task structs manually
 */
struct task *k_task;
struct task *curr;
struct task k;
k_task = &k;

struct task tasks[TASK_COUNT] = {0};
curr = k_task;

uint8_t stack_space[TASK_COUNT*STACK_SIZE] = {0};

struct stack s = { 
		.stack_space = &stack_space[0];
		.stack_num = TASK_COUNT;
		.stack_size = STACK_SIZE;
		};

struct request_entry *req_head;
struct request_entry req_entries[REQUEST_MAX] = {0};
req_head = &req_entries[0];



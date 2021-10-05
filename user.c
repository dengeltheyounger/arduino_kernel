#include "user.h"

/* Task structs defined here.
 * Leave k_task alone, define array of 
 * task structs manually
 */
struct task *k_task;
struct task *curr;
struct task k;
k_task = &k;

/* These are manually defined by user. I will eventually
 * turn them into defines to save data.
 */
task_count = 4;
struct task tasks[4] = {0};
// Leave this one alone
curr = k_task;

/* define this based on the number of tasks
 * and stack size
 */
uint8_t stack_space[32*4] = {0};

struct stack s = { 
		.stack_space = &stack_space[0];
		// Define this based on task count
		.stack_num = 4;
		// Define this based on stack size
		.stack_size = 32;
		};

struct request_entry *req_head;
/* Define this. Currently it needs to be equal to the
 * number of tasks. I plan to update it so that it can
 * exceed the number of tasks.
 */
uint16_t request_max = 4;
struct request_entry req_entries[4] = {0};
req_head = &req_entries[0];



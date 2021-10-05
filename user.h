#ifndef	USER_H
#define	USER_H
#include "tasks.h"
#include "request.h"
#include "stack.h"

/* The purpose of this is to define in the data and bss section a series
 * of variables that have currently been stored in stack. This will allow
 * the user more flexibility (although will require better understanding of
 * the kernel
 *
 * The data structures are declared here and then defined in the data structure
 */

// declare task structs here
extern uint8_t task_count;
extern struct task *curr;
extern struct task *k_task;

// Declare stack space here
extern struct stack s;

// declare request structs here
extern uint16_t request_max;
extern struct request_entry *req_head;
extern uint16_t request_max;

#endif

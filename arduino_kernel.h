#ifndef	ARDUINO_KERNEL_H
#define	ARDUINO_KERNEL_H
#include <stdlib.h>
#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "memory.h"
#include "tasks.h"
#include "stack.h"
#include "request.h"
#include "system.h"
#include "user.h"

extern struct task *curr;
extern struct task *k_task;

extern uint16_t request_max;

extern void set_timer();

/* Kernel main will take the number of tasks and then
 * a pointer to a task_funct pointers as arguments.
 * Kernel main will first create the necessary task
 * structs, it will give each task a stack to work with
 * and then it will begin running each task round robin.
 *
 * The kernel will only handle four tasks at a time. This
 * is due to the limited ram capacity. If there are more
 * than 4 tasks, then it will exit with error
 *
 * The ISR will take care of context switching
 */
int kernel_main(uint8_t task_count, 
		void (*task_funct[])(), 
		size_t ssize);

#endif

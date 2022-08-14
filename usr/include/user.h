#ifndef	USER_H
#define	USER_H
#include <avr/io.h>
#include <stdint.h>
#include <stddef.h>
#include "sys/tasks.h"
#include "sys/stack.h"
#include "sys/request.h"
#include "tmr/software_timer.h"
#include "net/ethernet.h"

// These are macros that relate to serial communicate, if desired
// Remove this macro in order to remove the code associated with usart
// Define CPU frequency for UBR calculation
#ifndef	F_OSC
#define	F_OSC	16UL
#endif

/* The purpose of this is to define in the data and bss section a series
 * of variables that have currently been stored in stack. This will allow
 * the user more flexibility (although will require better understanding of
 * the kernel
 *
 * The data structures are declared here and then defined in the data structure
 */
// This concerns the total number of tasks
#define	TASK_COUNT	1
// This concerns the total number of software timers

// The size of a given task's stack
#define	STACK_SIZE	32
// Total number of requests allowed.
// Currently, this must be equal to the number of tasks
#define	REQUEST_MAX	TASK_COUNT

#if USE_SOFTWARE_TIMER == 1
#define	SOFTWARE_TIMER_COUNT	5
#endif

/* This will need to be defined by the user in user.c */
extern void (*task_funct[TASK_COUNT])();

extern struct task tasks[TASK_COUNT];

extern struct task *curr;

#if	USE_SOFTWARE_TIMER == 1
extern volatile struct software_timer tmr_arr[];
#endif

extern struct stack s;

extern struct request_entry requests[REQUEST_MAX];

extern int request_array[REQUEST_MAX];

#endif

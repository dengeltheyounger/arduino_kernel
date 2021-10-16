#ifndef	USER_H
#define	USER_H
#include "tasks.h"
#include "request.h"
#include "stack.h"
#include "blink.h"

/* The purpose of this is to define in the data and bss section a series
 * of variables that have currently been stored in stack. This will allow
 * the user more flexibility (although will require better understanding of
 * the kernel
 *
 * The data structures are declared here and then defined in the data structure
 */
// This concerns the total number of tasks
#define	TASK_COUNT	4
// The size of a given task's stack
#define	STACK_SIZE	32
// Total number of requests allowed.
// Currently, this must be equal to the number of tasks
#define	REQUEST_MAX	4

// These are macros that relate to serial communicate, if desired
// Remove this macro in order to remove the code associated with usart
#define	USART_IMPLEMENTED
// Define CPU frequency for UBR calculation
#ifndef	F_CPU
#define	F_CPU	16UL
#endif

// Define Baud rate
#define	BAUD	9600

#define	ASYNC_NORM	~(1 << 1)

#define	ASYNC_DOUBLE	(1 << 1)

#define	MODE		UCSR0A &= ASYNC_NORM;	

#define	TRANSMIT	(1 << TXEN0)
#define	RECEIVE		(1 << RXEN0)

#define	TRANSMISSION	UCSR0B |= (TRANSMIT | RECEIVE);

/* This will need to be defined by the user in user.c */
extern void (*task_funct[TASK_COUNT])();

extern struct task *curr;

extern struct stack s;

extern uint16_t request_max;
extern struct request_entry *req_head;

#endif

#ifndef	USER_H
#define	USER_H
#include <avr/io.h>
#include "tasks.h"
#include "stack.h"
#include "blink.h"
#include "request.h"

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
#define	USART_ENABLED
// Define CPU frequency for UBR calculation
#ifndef	F_OSC
#define	F_OSC	16UL
#endif

// Define Baud rate
#define	BAUD			9600

#define	UBRR			UBBR0 = ((F_OSC / (16 * BAUD)) -1);

#define	USART_ASYNC_NORM	UCSR0A &= ~(1 << U2X0);	\
				UCSR0C &= ~((1 << UMSEL01) | (1 << UMSEL00));

#define	USART_ASYNC_DOUBLE	UCSR0A |= (1 << U2X0);

#define	USART_TRANSMIT		(1 << TXEN0)
#define	USART_RECEIVE		(1 << RXEN0)

#define	USART_TRANSMISSION	UCSR0B |= (TRANSMIT | RECEIVE);

#define	USART_PARITY_DISABLED	UCSR0C &= ~((1 << UPM01) | (1 << UPM00));
#define	USART_PARITY_EVEN	UCSR0C |= (1 << UPM01); UCSR0C &= ~(1 << UPM00);
#define	USART_PARITY_ODD	UCSR0C |= ((1 <<  UPM01) | (1 << UPM00));

#define	USART_STOP_ONE		UCSR0C &= ~(1 << USBS0);
#define	USART_STOP_TWO		UCSR0C |= (1 << USB0);

#define	USART_DATA_FIVE		UCRS0C &= ~((1 << UCSZ02) | (1 << UCSZ01) | (1 << UCSZ00));
#define	USART_DATA_SIX		UCSR0C |= (1 << UCSZ00); UCSR0C &= ~((1 << UCSZ02) | (1 << UCSZ01));
#define	USART_DATA_SEVEN	UCSR0C |= ((1 << UCSZ01); UCSR0C &= ~((1 << UCSZ02) | (1 << UCSZ00));
#define	USART_DATA_EIGHT	UCSR0C |= ((1 << UCSZ01) | (1 << UCSZ00)); UCSR0C &= ~(1 << UCSZ02);
#define	USART_DATA_NINE		UCSR0C |= ((1 << UCSZ02) | (1 << UCSZ01) | (1 << UCSZ00));

#define	USART_INIT		USART_STOP_ONE \
				USART_PARITY_DISABLED \
				USART_ASYNC_NORM \
				USART_TRANSMISSION \
				USART_DATA_EIGHT \
				UBBR0 \


/* This will need to be defined by the user in user.c */
extern void (*task_funct[TASK_COUNT])();

extern struct task tasks[TASK_COUNT];

extern struct task *curr;

extern struct stack s;

extern struct request_entry requests[REQUEST_MAX];

extern int request_array[REQUEST_MAX];

#endif

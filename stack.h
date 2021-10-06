#ifndef	STACK_H
#define	STACK_H
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <avr/io.h>

/* A big allocated stack. This is portioned out as needed for the various
 * tasks.
 */
struct stack {
	void *stack_space;
	size_t stack_num;
	size_t stack_size;
};

#endif

#ifndef	STACK_H
#define	STACK_H
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <avr/io.h>

/* A big heap allocated stack. This is portioned out as needed for the various
 * tasks.
 */
struct stack {
	void *stack_space;
	size_t stack_num;
	size_t stack_size;
};

/* Allocate memory for a new set of stacks. If calloc fails, return NULL */

static inline void new_stack_space(struct stack *s, 
					size_t stacknum, 
					size_t stacksize) {
	s->stack_space = NULL;
	s->stack_num = 0;
	s->stack_size = 0;

	/* Create an array of stack structs. 
	 * Return empty stack if calloc fails 
	 * Callocing this way allows for indexing
	 */
	s->stack_space = calloc(stacknum, stacksize);

	if (!s->stack_space) {
		return;
	}

	s->stack_num = stacknum;
	s->stack_size = stacksize;
}

/* Release all of the memory associated with the stack array. */

static inline void release_stacks(struct stack *s) {
	free(s->stack_space);
}

#endif

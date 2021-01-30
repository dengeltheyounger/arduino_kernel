#ifndef	STACK_H
#define	STACK_H
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <avr/io.h>
#ifndef	DEBUG
#define DEBUG
#endif

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

#ifdef	DEBUG
	printf("Entered new_stack_space\n");
	getchar();
#endif
	s->stack_space = NULL;
	s->stack_num = 0;
	s->stack_size = 0;

	/* Create an array of stack structs. 
	 * Return empty stack if calloc fails 
	 * Callocing this way allows for indexing
	 */
	s->stack_space = calloc(stacknum, stacksize);
#ifdef	DEBUG
	printf("Address of allocated stack space: %p\n", s->stack_space);
	printf("Number of stacks: %u\n", stacknum);
	printf("Size of each stack: %u\n", stacksize);
	getchar();
#endif

	if (!s->stack_space) {
#ifdef	DEBUG
	printf("Failed to allocated stack space. Exiting...\n");
	getchar();
#endif
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

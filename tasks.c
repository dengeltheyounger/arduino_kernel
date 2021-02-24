#include "tasks.h"

union splitter {
	void *tosplit;
	uint8_t split[2];
} addr_split;

void make_task(struct task *prev, struct task *current, void (*task_funct)()) {

	if (prev) {
		prev->next = current;
	}

	// Set task pointer and task state
	current->task_funct = task_funct;
	current->state = runnable;
}

int set_task_stacks(struct task *t, size_t task_num,
			struct stack *s, size_t stack_num) {
	// Exit error if there are more tasks than stacks
	if (stack_num < task_num)
		return 0;

	struct task *current = t;
	/* In order to simplify the lines, we're going to use these holders
	 * In addition, a void * is two bytes. For that reason we are dereferencing
	 * with a uint16_t.
	 */
	void *sspace = s->stack_space;
	size_t ssize = s->stack_size;

	for (size_t i = 0, ndx = 0; i < stack_num; ++i, ++ndx) {
		if (!current) {
			break;
		}
		/* Store the address of stack at index sp_start.
		 * Keep in mind that the stacks grow downward,
		 * so we're going to the end of the stack region
		 * rather than the beginning.
		 */
		current->stack_start = sspace+(ssize*ndx)+ssize-1;
		current->stack_ptr = current->stack_start;
		
		/* Write the address of do_task in the stack. It will act as
		 * the return address when the ISR is finished.
		 * In addition, we are going to store a preliminary status 
		 * register
		 */
		addr_split.tosplit = &do_task;

		// Set the top of stack as the address of do_task
		*(uint8_t *) current->stack_ptr = addr_split.split[0];
		*(uint8_t *) --(current->stack_ptr) = addr_split.split[1];

		// Prepare to set current's address in argument registers
		addr_split.tosplit = current;
		// Set up stack for context switch
		for (uint8_t i = 0; i < 32; ++i) {
			if (i != 24 && i != 25) {
				*(uint8_t *) --(current->stack_ptr) = 0;
			}

			else {
				*(uint8_t *) --(current->stack_ptr) = 
					addr_split.split[(i == 24) ? 0 : 1 ];
			}
		}

		// Set SREG
		*(uint8_t *) --(current->stack_ptr) = 0;
				
		current = current->next;
	}

	return 1;
}

void end_task(struct task *t) {
	t->state = complete;
	return;
}

void do_task(struct task *t) {
	
	t->task_funct();
	end_task(t);
	// Infinite loop because we're not supposed to return
	while(1);
}

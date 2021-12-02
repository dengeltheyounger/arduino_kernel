#include "tasks.h"

void make_task(struct task *p, struct task *current, void (*task_funct)()) {

	if (p) {
		p->next = current;
	}

	// Set task pointer
	current->task_funct = task_funct;
	// 26 and 25 contain curr as argument for do_task
	uint16_t addr = (uint16_t) current;
	current->c.r24 = ADDR_LO(addr);
	current->c.r25 = ADDR_HI(addr);
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
		current->c.sp_start = sspace+(ssize*ndx)+ssize-1;
		current->c.sp = current->c.sp_start;
		
		/* Write the address of do_task in the stack. It will act as
		 * the return address when the ISR is finished.
		 * In addition, we are going to store a preliminary status 
		 * register
		 */
		uint16_t addr = (uint16_t) do_task;
		uint8_t lower = ADDR_LO(addr);
		uint8_t upper = ADDR_HI(addr);
	
		*(uint8_t *) current->c.sp-- = lower;
		*(uint8_t *) current->c.sp-- = upper;
		*(uint8_t *) current->c.sp-- = 0;
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

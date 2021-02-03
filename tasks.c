#include "tasks.h"

union splitter {
	void *tosplit;
	uint8_t split[2];
} addr_split;

void make_task(struct task *prev, struct task *curr, void (*task_funct)()) {
#ifdef	DEBUG
	printf("In make task. Prev: %p. Curr %p\n", prev, curr);
	getchar();
#endif
	if (prev) {
		prev->next = curr;
#ifdef	DEBUG
		printf("curr is prev->next.\n");
		getchar();
#endif
	}

	// Set task pointer
	curr->task_funct = task_funct;
	// 26 and 25 contain curr as argument for do_task
	addr_split.tosplit = curr;
	curr->c.r25 = addr_split.split[0];
	curr->c.r26 = addr_split.split[1];

#ifdef	DEBUG
	printf("Address of task for curr: %p\n", task_funct);
	getchar();
#endif
	curr->state = runnable;
}

int set_task_stacks(struct task *t, size_t task_num,
			struct stack *s, size_t stack_num) {
	// Exit error if there are more tasks than stacks
	if (stack_num < task_num)
		return 0;

#ifdef	DEBUG
	printf("Entered set_task_stacks\n");
	printf("Address of task: %p\n", t);
	getchar();
#endif

	struct task *current = t;
	/* In order to simplify the lines, we're going to use these holders
	 * In addition, a void * is two bytes. For that reason we are dereferencing
	 * with a uint16_t.
	 */
	void *sspace = s->stack_space;
	// Pointer to the current task's stack poitner
	void *c_sp = NULL;
	size_t ssize = s->stack_size;

#ifdef	DEBUG
	printf("Preparing to iterate\n");
	getchar();
#endif

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
		c_sp = current->c.sp;
#ifdef	DEBUG	
		printf("Address of current: %p\n", current);
		printf("Stack start for current: %p\n", current->c.sp_start);
		getchar();
#endif

		/* Write the address of do_task in the stack. It will act as
		 * the return address when the ISR is finished.
		 * In addition, we are going to store a preliminary status 
		 * register
		 */
		addr_split.tosplit = &do_task;
		*(uint8_t *) c_sp = add_split.split[0];
		*(uint8_t *) --c_sp = add_split.split[1];
		*(uint8_t *) --c_sp = 0;
		current = current->next;
	}

	return 1;
}


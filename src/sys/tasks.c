#include "sys/tasks.h"

/*!
 *	\brief Initialize a task.
 *
 *	This consists of setting up the argument registers for "do_task" and
 *	then setting the task as runnable.
 *
 *	\param current
 *	The task struct currently being initialized.
 */
void make_task(struct task *current) {

	// 26 and 25 contain curr as argument for do_task
	uint16_t addr = (uint16_t) current;
	current->c.r24 = ADDR_LO(addr);
	current->c.r25 = ADDR_HI(addr);
	current->state = runnable;
}

/*!
 *	\brief Set up the stack for a given task.
 *
 *	The complexity is that the address of do_task needs to be added to the
 *	stack. The reason is that the housekeeper will then pop the address of
 *	do_task from the task's stack when the task is selected.
 *
 *	\param t
 *	The task for which the stack needs to be set up.
 *
 *	\param task_num
 *	The total number of tasks.
 *
 *	\param s
 *	The stack that the tasks will use.
 *
 *	\param stack_num
 *	The total number of stacks to be parceled.
 *
 *	\ret
 *	0 if there are more stacks than tasks, 1 if otherwise.
 *
 */
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

/*!
 *	\brief End a task.
 *
 *	This consists of setting a task state to complete. This will cause the
 *	task to be ignored in the linked list.
 *
 *	\param t
 *	The task to be ended.
 */
void end_task(struct task *t) {
	t->state = complete;
	return;
}

/*!
 *	\brief Run the task's callback.
 *
 *	\param t
 *	The task
 */
void do_task(struct task *t) {
	
	t->task_funct();
	end_task(t);
	// Infinite loop because we're not supposed to return
	while(1);
}


/*!
 *	\brief Find the next task to run.
 *
 *	\ret
 *	This always returns 1 if a runnable task was found, 0 otherwise.
 */
unsigned int get_next_task() {
	struct task *tmp = curr;
	struct task *t = curr->next;
	
	while (tmp != t) {
		if (t->state == runnable) {
			curr = t;
			return 1;
		}

		t = t->next;
	}

	return 0;
}


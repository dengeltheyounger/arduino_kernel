#ifndef	LIST_H
#define	LIST_H
#include <stdint.h>
#include <stdlib.h>
#include "tasks.h"

#define FOR_EACH_LIST_ENTRY(ITER)	\
	for (ITER = head; ITER != NULL; ITER = ITER->next)

struct list_entry {
	uint32_t value;
	struct task *t;
	struct list_entry *next;
};

extern struct list_entry *head;

/* Allocate space for a list entry. After that, add it to the
 * linked list. Return 1 for success and 0 for error
 */
int make_list_entry(struct task *t, uint32_t value);

/* This might not be necessary */
static inline struct list_entry *remove_entry_top() {
	struct list_entry *tmp = head;

	if (tmp == NULL)
		return NULL;

	head = head->next;
	head->t->state = runnable;
	free(tmp);

	return NULL;
}

#endif

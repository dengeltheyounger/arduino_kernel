#include "list.h"

struct list_entry *head = NULL;

int make_list_entry(struct task *t, uint32_t value) {
	struct list_entry *e = calloc(1, sizeof(struct list_entry));

	if (!e) {
		return 0;
	}

	// Set the desired time
	e->value = value;
	e->t = t;
	
	// Insert into the list
	struct list_entry *iter = NULL;
	struct list_entry *prev = NULL;
	
	if (!head) {
		head = e;
		return 1;
	}
	
	else if (!head->next) {
		head->next = e;
		return 1;
	}

	// Iterate through each of the entries
	FOR_EACH_LIST_ENTRY(iter) {
		/* If iter's value is greater than e's,
		 * then have e come before iter. Also check
		 * to see if iter is head. If it is, then
		 * reorient head
		 */
		
		if (iter->value > e->value) {
			
			e->next = iter;
						
			if (!prev) {
				head = e;
			} else {
				prev->next = e;
			}
			
			return 1;
		}

		// Set prev to the entry we're about to move on from
		prev = iter;
	}

	return 1;
}


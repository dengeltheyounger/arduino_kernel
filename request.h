#ifndef	REQUEST_H
#define	REQUEST_H
#include <stdint.h>
#include <stdlib.h>
#include "tasks.h"
#include "system.h"

enum active_req_status {
	inactive = 0,
	active = 1
};

struct request_entry {
	uint32_t value;
	struct task *t;
	enum active_req_status status;
};

extern struct request_entry *req_head;
extern uint16_t request_max;

/* Add the task to the next spot in the array */
void add_req_entry(struct task *t, uint32_t value);


/* Shift struct values through the first inactive index.
 * This way, index 0 has the values of index 1 and so on.
 */
void check_req_top();

#endif

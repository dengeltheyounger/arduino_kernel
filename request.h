#ifndef	REQUEST_H
#define	REQUEST_H
#include <stdint.h>
#include <stdlib.h>
#include "tasks.h"


enum active_req_status {
	inactive = 0,
	active = 1
};

struct request_entry {
	uint32_t value;
};

extern struct task tasks[];
extern struct request_entry requests [];
extern int request_array[];

#include "system.h"

/* Add the task to the next spot in the array */
void add_req_entry(uint8_t task_ndx, uint32_t value);


/* Shift struct values through the first inactive index.
 * This way, index 0 has the values of index 1 and so on.
 */
void check_req_top();

#endif

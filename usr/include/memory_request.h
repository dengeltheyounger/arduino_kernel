#ifndef	MEMORY_REQUEST_H
#define	MEMORY_REQUEST_H
#include <stdint.h>
#include <stddef.h>

#if USE_EEPROM_MEMORY == 1

struct memory_request {
	uint8_t task_ndx;
	uint8_t memory_space;
	uint16_t desired_pages;
};

extern struct memory_request *eeprom_ptr;
extern struct memory_request *flash_ptr;
extern uint8_t eeprom_req_count;
extern uint8_t flash_req_count;

#endif

#endif

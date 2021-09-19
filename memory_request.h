#ifndef	MEMORY_REQUEST_H
#define	MEMORY_REQUEST_H
#include <stdint.h>
#include <stddef.h>

/* The user should define the following macro here if
 * they wish to take advantage of memory io capabilites
 * of the kernel
 *
 * #ifndef	MEMORY_REQUESTED
 * #define	MEMORY_REQUESTED
 * #endif
 *
 * This lets the kernel know that it should add the magic number to
 * eeprom/flash/both in order to indicate that memory has been written
 * there (the purpose of this is to allow tasks to restore state if
 * there is a power failure).
 */

/* The user should define separate arrays of memory request
 * structs for eeprom and flash sections. When the kernel
 * is given a task index for memory_read or memory_write,
 * it will iterate through the array of memory_requests
 * in order to find the matching task index. This allows
 * for cases where not all tasks desire memory.
 *
 * The kernel will also expect that the memory_requests
 * elements will be defined in order of increasing task
 * index. This will allow the kernel to add up the number
 * of pages to get a total count for the sake of
 * getting an address.
 *
 * If the user should desire eeprom memory, they should name
 * the array "mem_req_eeprom".
 *
 * Likewise, if they desire flash memory, they should name
 * the array "mem_req_flash".
 *
 * Given some time, I might find an efficient setup, but
 * I hope that this makes a decent api for memory allocations
 * and reads. 
 */

#ifndef	MEMORY_REQUESTED
#define MEMORY_REQUESTED
#endif

struct memory_request {
	uint8_t task_ndx;
	uint8_t memory_space;
	uint16_t desired_pages;
};

#ifdef	MEMORY_REQUESTED
/* If these are needed, then the kernel will
 * expect them when handling the memory
 * request structs
 */

/*
extern struct memory_request *eeprom_ptr;
extern struct memory_request *flash_ptr;
extern uint8_t eeprom_req_count;
extern uint8_t flash_req_count;
*/
#endif

#endif

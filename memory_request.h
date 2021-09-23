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
 * This macro will define a set of functions that will
 * act as the api for handling memory IO. 
 */

/* The user should define separate arrays of memory request
 * structs for eeprom and flash sections. When the kernel
 * is given a task index for memory_read or memory_write,
 * it will iterate through the array of memory_requests
 * in order to find the matching task index. This allows
 * for cases where not all tasks desire memory.
 *
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
 * request structs.
 *
 * If you decide that you want to use the low level
 * read and write utilities by hand, go ahead and
 * just keep the pointers NULL.
 */


extern struct memory_request *eeprom_ptr;
extern struct memory_request *flash_ptr;
extern uint8_t eeprom_req_count;
extern uint8_t flash_req_count;

#endif

#endif

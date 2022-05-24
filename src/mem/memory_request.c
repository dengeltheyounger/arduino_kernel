#include "mem/memory_request.h"

#ifdef	MEMORY_REQUESTED

/* Define memory request struct arrays here.
 * Don't forget to set the pointers to the first
 * elements of the arrays in addition to setting
 * the request count's
 */

#define	EEPROM 1

struct memory_request mem_reqs[4] = {	{
					.task_ndx = 0, 
					/* For some reason, entering 
					 * 'eeprom' is leading to an error
					 */
					.memory_space = EEPROM,
					.desired_pages = 2
					},

					{
					.task_ndx = 1,
					.memory_space = EEPROM,
					.desired_pages = 2
					},

					{
					.task_ndx = 2,
					.memory_space = EEPROM,
					.desired_pages = 3
					},
					
					{
					.task_ndx = 3,
					.memory_space = EEPROM,
					.desired_pages = 2
					}
				};

struct memory_request *eeprom_ptr = &mem_reqs[0];
struct memory_request *flash_ptr = NULL;

uint8_t eeprom_req_count = 4;
uint8_t flash_req_count = 0;


#endif

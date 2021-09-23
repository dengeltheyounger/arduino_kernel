#include "memory_request.h"

#ifdef	MEMORY_REQUESTED

/* Define memory request struct arrays here.
 * Don't forget to set the pointers to the first
 * elements of the arrays in addition to setting
 * the request count`s
 */

struct memory_request *eeprom_ptr = NULL;
struct memory_request *flash_ptr = NULL;

uint8_t eeprom_req_count = 0;
uint8_t flash_req_count = 0;

#endif

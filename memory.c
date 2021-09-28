#include "memory.h"

#ifdef	MEMORY_REQUESTED

#define ITERATE_ZONE_STRUCT(ZONE)	\
	for (int i = 0; i < ZONE ## _req_count; ++i)	\

int memory_write(int task_id,
		enum memory_space zone,
		uint16_t begin,
		uint16_t end,
		unsigned char *buffer) {

	/* If both pointers are NULL or both request counts
	 * are 0, then we'll exit because the programmer
	 * did not fill out their paperwork.
	 */
	if ((eeprom_ptr == NULL && flash_ptr == NULL) ||
		(eeprom_req_count == 0 && flash_req_count == 0)) {
		return 0;
	}
	
	uint16_t address = 0;
	uint16_t size = 0;

	/* Page size is 4 bytes for eeprom */
	if (zone == eeprom) {
		/* I'm going to assume that the user is not going
		 * to try to access memory space for a task not 
		 * represented in the data structure.
		 */
		ITERATE_ZONE_STRUCT(eeprom) {
			/* Iterate until we get to our task id or the end */
			if (eeprom_ptr[i].task_ndx == task_id) {
				size = eeprom_ptr[i].desired_pages * 4;
				break;
			}
			/* add desired_pages * 4 to get byte width address */
			address += eeprom_ptr[i].desired_pages * 4;
		}

		if (end - begin > size) {
			return 0;
		}

		eeprom_write((void *) address, begin, end, buffer);
	}


	// If we got to this point we were successful
	return 1;
}

int memory_read(int task_id,
		enum memory_space zone,
		uint16_t begin,
		uint16_t end,
		unsigned char *buffer) {

	if (eeprom_ptr == NULL && flash_ptr == NULL ||
		(eeprom_req_count == 0 && flash_req_count == 0)) {
		return 0;
	}

	uint16_t address = 0;
	uint16_t size = 0;

	if (zone == eeprom) {
		ITERATE_ZONE_STRUCT(eeprom) {
			if (eeprom_ptr[i].task_ndx == task_id) {
				size = eeprom_ptr[i].desired_pages * 4;
				break;
			}

			address += eeprom_ptr[i].desired_pages * 4;
		}

		if (end - begin > size) {
			return 0;
		}

		eeprom_read((void *) address, begin, end, buffer);
	}

	return 1;
}

#endif

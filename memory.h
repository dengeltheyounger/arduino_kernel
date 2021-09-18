#ifndef	MEMORY_H
#define	MEMORY_H
#include "tasks.h"

#define	EEPROM_PGSIZE		4
#define	EEPROM_PGCOUNT		250
#define	FLASH_WORD_PGSIZE	64
#define	FLASH_WORD_PGCOUNT	256

enum memory_space {
	eeprom = 1,
	flash = 2
};

/* The idea is that the programmer will fill an
 * array that will contain the task's id (an index
 * for the set of tasks), as well as the desired
 * size for eeprom (0 if none) and the desired size
 * for the flash. From here, the kernel is able to 
 * infer where the task's location in memory is.
 *
 * If the there is an error, the kernel will return
 * 0 (false). Eventually, it would be useful for me
 * to include error codes in these functions.
 */


/* Memory write will write the buffer to the task's
 * space.
 *
 * 1 indicates success
 * 0 indicates error
 */
int memory_write(int task_id, 
		enum memory_space zone,
		char *buffer,
		int n_bytes);

/* read contents of task's memory space
 * into the buffer. This will mean either
 * the entire memory space or the number of
 * bytes, whichever is smallest.
 * 
 * 1 indicates success
 * 0 indicates error
 */
int memory_read(int task_id,
		enum memory_space zone,
		char *buffer,
		int n_bytes);
		
#endif

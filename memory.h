#ifndef	MEMORY_H
#define	MEMORY_H
#include <avr/io.h>
#include "tasks.h"
#include "memory_request.h"

#define	EEPROM_PGSIZE		4
#define	EEPROM_PGCOUNT		250
#define	FLASH_WORD_PGSIZE	64
#define	FLASH_WORD_PGCOUNT	256


/* The reason why I use this macro is because
 * it may save on memory in the event that
 * the user does not desire to use any of the
 * memory io functions. 
 *
 * Given the power of GCC, it is likely that 
 * it will disinclude any memory io functions that
 * are not used anyway. However, this maybe this will
 * add a little safeguard, just in case (or maybe its
 * inefficient)
 */

#ifdef MEMORY_REQUESTED

enum memory_space {
	eeprom = 1,
	flash = 2
};

static inline unsigned char eeprom_read_byte(void *addr) {

	// Wait for completion of previous write
	while (EECR & (1 << EEPE));

	// Set up address register
	EEAR = (uint16_t) addr;

	/* This might be an area where a read can
	 * fail if an interrupt is generated. I
	 * don't really know, to be honest.
	 */
	asm("cli\n\t");
	// Start eeprom read by
	EECR |= (1 << EERE);
	asm("sei\n\t");

	// Return data from data register
	return EEDR;
}

static inline void eeprom_read(void *addr,
			unsigned char *buffer,
			int n_bytes) {

	/* Read the total number of requested bytes from eeprom
	 * into buffer
	 */
	for (int i = 0; i < n_bytes; ++i) {
		buffer[i] = eeprom_read_byte((void *) 
						((unsigned int) addr + i));
	}
}

static inline void eeprom_write_byte(void *addr,
				unsigned char data) {

	// This came from the data sheet
	// Wait for completion of previous write
	while (EECR & (1 << EEPE));

	// Write new EEPROM address to EEAR
	EEAR = (uint16_t) addr;

	// Write new EEPROM data to EEDR
	EEDR = data;
	
	/* During this portion, it is important to clear interrupts in order to
	 * ensure write success
	 */
	asm("cli\n\t");
	// Write a logical one to the EEMPE bit while writing a zero to EEPE in EECR
	EECR |= (1 << EEMPE);
	EECR |= (1 << EEPE);
	asm("sei\n\t");

	return;
}

static inline void eeprom_write(void *addr,
			unsigned char *data,
			int n_bytes) {
	
	// Write each byte to eeprom
	for (int i = 0; i < n_bytes; ++i) {
		eeprom_write_byte((void *)((unsigned int) addr + i), data[i]);
	}

	return;
}
	

/* Determine whether or not the magic number has been written.
 * If it has not, then memory has not been written into the
 * eeprom/flash.
 *
 * Return 0 to indicate that the memory space has not been 
 * written into previously.
 *
 * Return 1 to indicate that the memory space has been written
 * into.
 */
static inline int probe_magic_number(enum memory_space space) {
	unsigned char buffer[2] = {0};
	
	/* If space is eeprom, then read first two bytes to determine
	 * if it has been written to.
	 */
	if (space == eeprom)
		eeprom_read(0, &buffer[0], 2);

	/* When the ability to read/write to flash memory has been implemented,
	 * then we will add an else statement here.
	 */

	else return 0;

	/* If we find the magic number written into the first four
	 * bytes, then return true. Otherwise, return false.
	 */

	if ((unsigned short int) buffer == 0xBABA) return 1;
	
	else return 0;
}

static inline void write_magic_number(enum memory_space space) {
	/* If the space is eeprom, then write the magic number
	 * to the first two bytes.
	 */

	unsigned char buffer[2] = {0xBA,0xBA};

	if (space == eeprom)
		eeprom_write(0, &buffer[0], 2);

	/* When we add code to handle flash memory,
	 * we will add it here.
	 */
	else return;
}

/* The idea is that the programmer will fill a
 * datastructure that will contain the task's id (an index
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
#endif

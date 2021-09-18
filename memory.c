#include "memory.h"

int memory_write(int task_id,
		enum memory_space zone,
		char *buffer,
		int n_bytes) {
	
	return 0;
}

inline unsigned char eeprom_read_byte(void *addr) {

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

inline void eeprom_read(void *addr,
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

inline void eeprom_write_byte(void *addr,
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

inline void eeprom_write(void *addr,
			unsigned char *data,
			int n_bytes) {
	
	// Write each byte to eeprom
	for (int i = 0; i < n_bytes; ++i) {
		eeprom_write_byte((void *)((unsigned int) addr + i), data[i]);
	}

	return;
}
			

int memory_read(int task_id,
		enum memory_space zone,
		char *buffer,
		int n_bytes) {

	return 0;
}

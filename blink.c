#include "blink.h"

// It is assumed that buffer has two elements
static inline int check_magic_number(uint8_t task_ndx, enum memory_space space,
					unsigned char *buffer) {

	int result = memory_read(task_ndx, space, 0, 2, buffer);

	if (!result) {
		return -1;
	}

	uint16_t *magic_number = (uint16_t *) &buffer[0];

	if (*magic_number == 0xB0B0) {
		return 1;
	}

	else {
		return 0;
	}
}


// Red LED
void blink1(void) {
	DDRB |= _BV(DDB5);

	/* This code is mainly to test the memory io api. Basically,
	 * check a magic number in the beginning of your space. If
	 * it is there, then load the settings from eeprom. If not,
	 * then write to the eeprom and load the settings. 
	 *
	 * This probably isn't how it would go in a commercial setting,
	 * but it will ensure that the memory api works.
	 */
	unsigned char buffer[8] = {0};
	uint16_t *magic_number = (uint16_t *) &buffer[0];
	// Clear the magic number so that we can check changes
	memory_write(0, eeprom, 0, 2, &buffer[0]);
	// byte 2
	uint8_t first_state = 0;
	// bytes 3 and 4
	uint16_t *first_length = (uint16_t *) &buffer[3];
	// byte 5
	uint8_t second_state = 0;
	// bytes 6 and 7
	uint16_t *second_length = (uint16_t *) &buffer[6];

	int result = check_magic_number(0, eeprom, &buffer[0]);	

	// Something went wrong. Exit
	if (result == -1) {
		return;
	}
		
	else if (result == 1) {
		// Read settings from eeprom
		memory_read(0, eeprom, 0, 8, &buffer[0]);
		// Whether or not it is on or off
		first_state = buffer[2];
		second_state = buffer[5];
	}

	else {
		// Fill buffer and write settings to eeprom
		*magic_number = 0xB0B0;
		buffer[2] = _BV(PORTB5);
		*first_length = 1000;
		buffer[5] = ~_BV(PORTB5);
		*second_length = 1000;
		memory_write(0, eeprom, 0, 8, &buffer[0]);
		memset(&buffer[0], 0, 8);
		memory_read(0, eeprom, 0, 8, &buffer[0]);
		first_state = buffer[2];
		second_state = buffer[5];
	}
	
	// On for second, off for a second
	while (1) {
		PORTB |= first_state;
		task_sleep(*first_length);
		PORTB &= second_state;
		task_sleep(*second_length);
	}
}

// Green LED
void blink2(void) {
	DDRB |= _BV(DDB4);
	unsigned char buffer[8] = {0};
	// bytes 0 and 1
	uint16_t *magic_number = (uint16_t *) &buffer[0];
	memory_write(1, eeprom, 0, 2, &buffer[0]);
	// byte 2
	uint8_t first_state = 0;
	// bytes 3 and 4
	uint16_t *first_length = (uint16_t *) &buffer[3];
	// byte 5
	uint8_t second_state = 0;
	// bytes 6 and 7
	uint16_t *second_length = (uint16_t *) &buffer[6];

	int result = check_magic_number(1, eeprom, &buffer[0]);

	if (result == -1) {
		return;
	}

	else if (result == 1) {
		memory_read(1, eeprom, 0, 8, &buffer[0]);
		first_state = buffer[2];
		second_state = buffer[5];
	}

	else {
		*magic_number = 0xB0B0;
		buffer[2] = ~_BV(PORTB4);
		*first_length = (uint16_t) 1000;
		buffer[5] = _BV(PORTB4);
		*second_length = (uint16_t) 1000;
		memory_write(1, eeprom, 0, 8, &buffer[0]);
		memset(&buffer[0], 0, 8);
		memory_read(1, eeprom, 0, 8, &buffer[0]);
		first_state = buffer[2];
		second_state = buffer[5];
	}

	// Off for a second, on for a second
	while (1) {
		PORTB &= first_state;
		task_sleep(*first_length);
		PORTB |= second_state;
		task_sleep(*second_length);
	}
}

// Blue LED
void blink3(void) {
	DDRB |= _BV(DDB3);
	unsigned char buffer[11] = {0};
	uint16_t *magic_number = (uint16_t *) &buffer[0];
	memory_write(2, eeprom, 0, 2, &buffer[0]);
	// byte 2
	uint8_t first_state = _BV(PORTB3);
	// byte 3
	uint8_t first_length = 250;
	// byte 4
	uint8_t second_state = ~_BV(PORTB3);
	// byte 5
	uint8_t second_length = 250;
	// byte 6
	uint8_t third_state = _BV(PORTB3);
	// byte 7
	uint8_t third_length = 250;
	// byte 8
	uint8_t fourth_state = ~_BV(PORTB3);
	// bytes 9 and 10
	uint16_t *fourth_length = (uint16_t *) &buffer[9];

	int result = check_magic_number(2, eeprom, &buffer[0]);

	if (result == -1) {
		return;
	}

	else if (result == 1) {
		memory_read(2, eeprom, 0, 11, &buffer[0]);
		first_state = buffer[2];
		first_length = buffer[3];
		second_state = buffer[4];
		second_length = buffer[5];
		third_state = buffer[6];
		third_length = buffer[7];
		fourth_state = buffer[8];
	}

	else {
		*magic_number = 0xB0B0;
		buffer[2] = _BV(PORTB3);
		buffer[3] = 250;
		buffer[4] = ~_BV(PORTB3);
		buffer[5] = 250;
		buffer[6] = _BV(PORTB3);
		buffer[7] = 250;
		buffer[8] = ~_BV(PORTB3);
		*fourth_length = 1000;
		memory_write(2, eeprom, 0, 11, &buffer[0]);
		memset(&buffer[0], 0, 11);
		memory_read(2, eeprom, 0, 11, &buffer[0]);
		first_state = buffer[2];
		first_length = buffer[3];
		second_state = buffer[4];
		second_length = buffer[5];
		third_state = buffer[6];
		third_length = buffer[7];
		fourth_state = buffer[8];
	}

	// Blink twice and then wait a second
	while (1) {
		PORTB |= buffer[2];
		task_sleep(buffer[3]);
		PORTB &= buffer[4];
		task_sleep(buffer[5]);
		PORTB |= buffer[6];
		task_sleep(buffer[7]);
		PORTB &= buffer[8];
		task_sleep(*fourth_length);

	}
}

// Yellow LED
void blink4(void) {
	DDRB |= _BV(DDB2);
	unsigned char buffer[8] = {0};
	uint16_t *magic_number = (uint16_t *) &buffer[0];
	memory_write(3, eeprom, 0, 2, &buffer[0]);

	// byte 2
	uint8_t first_state = 0;
	// bytes 3 and 4
	uint16_t *first_length = (uint16_t *) &buffer[3];
	// byte 5
	uint8_t second_state = 0;
	// bytes 6 and 7
	uint16_t *second_length = (uint16_t *) &buffer[6];

	int result = check_magic_number(3, eeprom, &buffer[0]);

	if (result == -1) {
		return;
	}
	
	else if (result == 1) {
		memory_read(3, eeprom, 0, 8, &buffer[0]);
		first_state = buffer[2];
		second_state = buffer[5];
	}

	else {
		*magic_number = 0xB0B0;
		buffer[2] = _BV(PORTB2);
		*first_length = 500;
		buffer[5] = ~_BV(PORTB2);
		*second_length = 500;
		memory_write(3, eeprom, 0, 8, &buffer[0]);
		memset(&buffer[0], 0, 8);
		memory_read(3, eeprom, 0, 8, &buffer[0]);
		first_state = buffer[2];
		second_state = buffer[5];
	}

	while (1) {
		PORTB |= buffer[2];
		task_sleep(*first_length);
		PORTB &= buffer[5];
		task_sleep(*second_length);
	}
}

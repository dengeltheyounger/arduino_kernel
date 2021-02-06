#include "arduino_kernel.h"
#include "blink.h"
#include <stdio.h>

/* The purpose of prep_kernel is to provide a location for the
 * programmer to set up the array of function pointers and the
 * provide the appropriate arguments to kernel main.
 */

int main() {
	int retval = 0;

	void (*tasks[])() = { &blink1, &blink2, &blink3, &blink4 };
	uint8_t tasknum = 4;

	retval = kernel_main(tasknum, tasks, 128);

	return retval;
}

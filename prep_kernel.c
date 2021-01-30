#include "arduino_kernel.h"
#include "blink.h"
#define DEBUG
#ifdef	DEBUG
	#include "uart.h"
#endif

/* The purpose of prep_kernel is to provide a location for the
 * programmer to set up the array of function pointers and the
 * provide the appropriate arguments to kernel main.
 */

int main() {
	int retval = 0;
#ifdef DEBUG
	uart_init();
	stdout = &uart_output;
	stdin = &uart_input;
	printf("Running kernel in debug mode...\n");
	getchar();
#endif
	

	void (*tasks[])() = { &blink };
	uint8_t tasknum = 1;
#ifdef	DEBUG
	printf("Addresses of tasks provided: \n");
	for (uint8_t i = 0; i < tasknum; ++i)
		printf("Task %u, %p\n", i, tasks[i]);
	getchar();
#endif
	retval = kernel_main(tasknum, tasks, 128);
#ifdef	DEBUG
	printf("Critical error! Not supposed to return from kernel_main!\n");
	getchar();
#endif

	return retval;
}

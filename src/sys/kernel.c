#include "sys/kernel.h"
#include "sys/system.h"

uint8_t kernel_stack[KERNEL_STACK_SIZE] = {0};

struct task kernel_task = {
	.c = 
	{
		.sp_start = &kernel_stack[KERNEL_STACK_SIZE - 1],
		.sp = &kernel_stack[0],
		.r0 = 0,
		.r1 = 0,
		.r2 = 0,
		.r3 = 0,
		.r4 = 0,
		.r5 = 0,
		.r6 = 0,
		.r7 = 0,
		.r8 = 0,
		.r9 = 0,
		.r10 = 0,
		.r11 = 0,
		.r12 = 0,
		.r13 = 0,
		.r14 = 0,
		.r15 = 0,
		.r16 = 0,
		.r17 = 0,
		.r18 = 0,
		.r19 = 0,
		.r20 = 0,
		.r21 = 0,
		.r22 = 0,
		.r23 = 0,
		.r24 = 0,
		.r25 = 0,
		.r26 = 0,
		.r27 = 0,
		.r28 = 0,
		.r29 = 0,
		.r30 = 0,
		.r31 = 0
	},
	.state = runnable,
	.task_funct = kernel_task_funct,
	.next = &tasks[0]
};

/*
 * Currently, the kernel task doesn't do anything.
 */
void kernel_task_funct() {
	// Awaken all sleeping_tasks that are due to wake up
	awaken_tasks();
	// Set the sleep time for when the next task wakes up
	task_sleep(TASK_COUNT, requests[request_array[0]].value);
}

#ifndef	KERNEL_H
#define	KERNEL_H
#include "sys/tasks.h"

#define	KERNEL_STACK_SIZE		0x20

extern struct task kernel_task;

void kernel_task_funct();

#endif

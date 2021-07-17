#ifndef	SYSTEM_H
#define	SYSTEM_H
#include <stdint.h>
#include "list.h"

void task_yield();

int task_sleep(uint32_t time);

#endif

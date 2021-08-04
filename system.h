#ifndef	SYSTEM_H
#define	SYSTEM_H
#include <stdint.h>
#include "list.h"

extern void call_housekeeper;

static inline void task_yield() {
	asm(
		"jmp	call_housekeeper\n\t"
	);
}

int task_sleep(uint32_t time);

#endif

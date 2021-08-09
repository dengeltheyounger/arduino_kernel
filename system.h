#ifndef	SYSTEM_H
#define	SYSTEM_H
#include <stdint.h>
#include "list.h"

struct sys_clock {
	volatile uint32_t time;	
};

extern volatile struct sys_clock system_time;

extern void call_housekeeper();

static inline void task_yield() {
	asm(
		"call	housekeeper_prelude\n\t"
	);
}

int task_sleep(uint32_t time);

#endif

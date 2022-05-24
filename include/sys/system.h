#ifndef	SYSTEM_H
#define	SYSTEM_H
#include <stdint.h>
#include "request.h"
#include "usr/user.h"

struct sys_clock {
	volatile uint32_t time;	
};

extern volatile struct sys_clock system_time;

static inline void task_yield() {
	asm(
		"call	housekeeper_prelude\n\t"
	);
}

void task_sleep(uint8_t task_ndx, uint32_t time);

#endif

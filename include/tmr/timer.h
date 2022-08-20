#ifndef	TIMER_H
#define	TIMER_H
#include "comm/usart.h"
#include "tmr/software_timer.h"

#if	DEBUG == 1
static inline void print_sys_timer_start() {
	println("In system timer ISR",
		STRLEN("In system timer ISR"));
}

static inline void print_sys_timer_end() {
	println("Out of system timer ISR",
		STRLEN("Out of system timer ISR"));
}

#endif

void init_timers();

void set_sys_timer();

#if USE_SOFTWARE_TIMER == 1

void set_usr_timer();

#endif

#endif

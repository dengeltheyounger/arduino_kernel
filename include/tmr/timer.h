#ifndef	TIMER_H
#define	TIMER_H
#include "tmr/software_timer.h"

void init_timers();

void set_sys_timer();

#if USE_SOFTWARE_TIMER == 1

void set_usr_timer();

#endif

#endif

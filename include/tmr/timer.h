#ifndef	TIMER_H
#define	TIMER_H

void init_timers();

void set_sys_timer();

#if USE_SOFTWARE_TIMER == 1

void set_usr_timer();

#endif

#endif

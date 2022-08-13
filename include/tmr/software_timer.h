#ifndef	SOFTWARE_TIMER_H
#define	SOFTWARE_TIMER_H
#include <stdint.h>
#include "util/queue.h"

#if USE_SOFTWARE_TIMER == 1

enum timer_state
{
	timer_stopped = 0,
	timer_started = 1
};

enum timer_type
{
	sw_timer_one_shot,
	sw_timer_periodic
};

struct software_timer
{
	uint8_t id;
	uint32_t period;
	uint32_t counter;
	enum timer_type;	
	enum timer_state state;
	void (*callback)();
}__attribute__((packed));

void init_software_timers();

void software_timer_start(volatile struct software_timer *tmr);

void software_timer_stop(volatile struct software_timer *tmr);

#endif

#endif

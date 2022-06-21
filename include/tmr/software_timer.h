#ifndef	SOFTWARE_TIMER_H
#define	SOFTWARE_TIMER_H
#include <stdint.h>
#include "util/queue.h"

enum timer_state
{
	timer_started,
	timer_stopped
};

struct software_timer
{
	uint8_t id;
	uint32_t period;
	enum timer_state state;
	void (*callback)();
};

void init_software_timers(struct software_timer *tmr_arr, uint8_t size);

void timer_start(struct software_timer *tmr);

void timer_stop(struct software_timer *tmr);

#endif

#ifndef	SOFTWARE_TIMER_H
#define	SOFTWARE_TIMER_H
#include <stdint.h>
#include "util/queue.h"

enum timer_state
{
	timer_stopped = 0,
	timer_started = 1
};

struct software_timer
{
	uint8_t id;
	uint32_t period;
	uint32_t counter;
	enum timer_state state;
	void (*callback)();
}__attribute__((packed));

void init_software_timers();

void timer_start(struct software_timer *tmr);

void timer_stop(struct software_timer *tmr);

#endif

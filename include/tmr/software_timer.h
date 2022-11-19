#ifndef	SOFTWARE_TIMER_H
#define	SOFTWARE_TIMER_H
#include <stdint.h>
#include "util/queue.h"
#include "sys/tasks.h"

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
	enum timer_type t;	
	enum timer_state state;
	void (*callback)();
}__attribute__((packed));

extern volatile struct task software_timer_task; 

void init_software_timers();

void software_timer_start(struct software_timer *tmr);

void software_timer_stop(struct software_timer *tmr);

#endif

#endif

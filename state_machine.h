#ifndef	STATE_MACHINE_H
#define	STATE_MACHINE_H
#include <stdarg.h>

enum sm_ret
{
	init_state_empty,
	next_state_empty
};

struct state
{
	// The first argument must always be the number of arguments
	va_list init_parameters;
	void (*init_state)(va_list args);
	struct state *(*do_state)(struct state *s);
	void (*deinit_state)();
};

struct state_machine
{
	struct state *current;
	struct state *prev;
};

struct state *Do_State(struct state *s);
	
enum sm_ret Run_State_Machine(struct state_machine sm);

#endif

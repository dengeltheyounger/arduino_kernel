#ifndef	STATE_MACHINE_H
#define	STATE_MACHINE_H
#include <stdarg.h>
#include "app_utilities/event.h"

struct state
{
	void (*init_state)(struct state *s);
	// The first argument must always be the number of arguments
	struct state *(*do_state)(struct state *s);
	void (*deinit_state)(struct state *s);
	void (*dispatch)(struct state *s, enum event e, int *handled);
};

/*
 * The state machine's pointer to previous is the next higher nesting. The 
 * purpose is to make it convenient to hand events up the states.
 */
struct state_machine
{
	struct state *current;
	struct state *prev;
	void (*init_state_machine)(struct state_machine *sm);
	void (*do_state_machine(struct state_machine *sm);
	void (*deinit_state_machine)(struct state_machine *sm);
};

struct state *Do_State(struct state *s);
	
void Run_State_Machine(struct state_machine *sm);

void empty_state_machine_handler(struct state_machine *sm);

void empty_state_handler(struct state *s);

#endif

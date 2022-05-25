#include "state_machine.h"

struct state *Do_State(struct state *s)
{
	struct state *next;
	s->init_state(s->args);
	next = s->do_state(s);
	
	s->deinit_state(s);

	return next;
}

void Run_State_Machine(struct state_machine *sm)
{

	sm->init_state_machine(sm);

	sm->do_state_machine(sm);

	sm->deinit_state_machine(sm);
}

void empty_state_machine_handler(struct state_machine *sm)
{
	return;
}

void empty_state_handler(struct state *s)
{
	return;
}

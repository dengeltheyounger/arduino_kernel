#include "state_machine.h"

struct state *Do_State(struct state *s)
{
	struct state *next;
	s->init_state(s->args);
	next = s->do_state(s);
	
	s->deinit_state(s);

	return next;
}

enum sm_ret Run_State_Machine(struct state_machine sm)
{
	struct state *next;

	if (sm->current == NULL)
	{
		return init_state_empty;
	}

	while (1)
	{
		next = Do_State(sm->current);
		
		if (next == NULL)
		{
			return next_state_empty;
		}

		sm->prev = sm->current;
		sm->current = sm->next;
	}
}

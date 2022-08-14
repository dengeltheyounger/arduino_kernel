#include "sys/mutex.h"

void hold_mutex(struct mutex *m) {
	while (m->held);

	m->held = 1;
}

void release_mutex(struct mutex *m) {
	m->held = 0;
}

#ifndef	MUTEX_H
#define	MUTEX_H
#include <stdint.h>

struct mutex {
	uint8_t held;
};

void hold_mutex(struct mutex *m);

void release_mutex(struct mutex *m);

#endif

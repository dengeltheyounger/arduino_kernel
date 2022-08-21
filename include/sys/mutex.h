#ifndef	MUTEX_H
#define	MUTEX_H
#include <stdint.h>
#include <util/atomic.h>

struct mutex {
	uint8_t held;
};

static inline void hold_mutex(struct mutex *m) {
	while (m->held);
	
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		m->held = 1;
	}
}

static inline void release_mutex(struct mutex *m) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		m->held = 0;
	}
}

static inline void hold_mutex_or_return(struct mutex *m) {
	if (m->held) {
		return;
	}

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		m->held = 0;
	}
}

#endif

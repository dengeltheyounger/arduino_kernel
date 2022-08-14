#ifndef	MUTEX_H
#define	MUTEX_H

struct mutex {
	int held;
};

void hold_mutex(struct mutex *m);

void release_mutex(struct mutex *m);

#endif

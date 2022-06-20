#ifndef	QUEUE_H
#define	QUEUE_H
#include <stdint.h>

struct queue
{
	uint32_t queue_size;
	uint32_t head;
	uint32_t tail;
	void *items[];
};

int enqueue(struct queue *q, void *item);

void *dequeue(struct queue *q);

#endif

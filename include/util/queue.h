#ifndef	QUEUE_H
#define	QUEUE_H
#include <stdint.h>
#include <stddef.h>

struct queue
{
	uint8_t queue_size;
	uint8_t head;
	uint8_t tail;
	void *items[];
}__attribute__((packed));

int enqueue(struct queue *q, void *item);

void *dequeue(struct queue *q);

#endif

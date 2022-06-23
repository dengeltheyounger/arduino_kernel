#ifndef	QUEUE_H
#define	QUEUE_H
#include <stdint.h>
#include <stddef.h>

struct queue
{
	uint16_t queue_size;
	uint16_t capacity;
	uint16_t head;
	uint16_t tail;
	void *items[];
}__attribute__((packed));

int enqueue(struct queue *q, void *item);

void *dequeue(struct queue *q);

#endif

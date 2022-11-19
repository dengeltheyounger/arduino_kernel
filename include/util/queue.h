#ifndef	QUEUE_H
#define	QUEUE_H
#include <stdint.h>
#include <stddef.h>

struct queue
{
	uint8_t size;
	uint8_t capacity;
	uint8_t head;
	uint8_t tail;
	void *items[];
}__attribute__((packed));

int enqueue(struct queue *q, void *itm);

void *dequeue(struct queue *q);

int queue_is_empty(struct queue *q);

int queue_is_full(struct queue *q);

#endif

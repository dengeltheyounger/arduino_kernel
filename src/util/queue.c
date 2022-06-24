#include "util/queue.h"

/*
 *	\brief Add an item into a queue.
 *
 *	\param q
 *	The queue into which the item will be added.
 *
 * 	\param item
 * 	The item to be added into the queue.
 *
 * 	\ret
 * 	0 for error and 1 for success.
 */
int enqueue(struct queue *q, void *item) {
	uint16_t tail = q->tail;
	uint16_t queue_size = q->queue_size;
	uint16_t capacity = q->capacity;

	if (capacity + 1 > queue_size)
	{
		return 0;
	}

	q->items[tail] = item;
	q->capacity++;
	q->tail = ++(q->tail) % queue_size;

	return 1;
}

/*
 *	\brief Remove an item from a queue.
 *
 *	\param q
 *	The queue from which the item will be removed.
 *
 *	\ret
 *	NULL if the queue is empty, or the item (which is a pointer).
 */
void *dequeue(struct queue *q) {
	uint16_t head = q->head;
	uint16_t capacity = q->capacity;
	void *ret;

	if (capacity == 0) {
		return NULL;
	}

	ret = q->items[q->head++];
	q->capacity--;

	return ret;
}

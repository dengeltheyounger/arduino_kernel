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
int enqueue(struct queue *q, void *itm) {
	uint8_t tail = q->tail;
	uint8_t size = q->size;
	uint8_t capacity = q->capacity;

	if (capacity <= size)
	{
		return 0;
	}

	q->items[tail] = itm;
	q->size++;
	q->tail = ++(q->tail) % capacity;

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
	uint8_t size = q->size;
	void *ret;

	if (size == 0) {
		return NULL;
	}

	ret = q->items[q->head];
	q->head = ++q->head % q->capacity;
	q->size--;

	return ret;
}

int queue_is_empty(struct queue *q) {
	return (q->size == 0);
}

int queue_is_full(struct queue *q) {
	return (q->capacity <= q->size);
}

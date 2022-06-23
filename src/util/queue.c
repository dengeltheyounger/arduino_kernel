#include "util/queue.h"

/*
 * Determine whether or not there is enough capacity. If not, then return
 * false.
 * After that, add the next item, and then increment the tail.
 * Set the new capacity.
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
 * Check to see if the capacity is greater than 0. If not, return NULL.
 * Get the next item from the queue. Increment the head, and decrement the
 * capacity. After that, return the item.
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

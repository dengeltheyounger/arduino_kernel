#include "util/queue.h"

int enqueue(struct queue *q, void *item) {
	uint32_t head = q->next_ndx;
	uint32_t queue_size = q->queue_size;

	if (head + 1 > queue_size) {
		return 0;
	}

	q->items[q->head++] = item;

	return 1;
}

void *dequeue(struct queue *q) {
	uint32_t tail = q->tail;
	uint32_t head = q->head;

	if (tail + 1 > head) {
		return NULL;
	}

	return q->[q->tail++];
}

#include "util/queue.h"

int enqueue(struct queue *q, void *item) {
	uint8_t head = q->head;
	uint8_t queue_size = q->queue_size;

	if (head + 1 > queue_size) {
		return 0;
	}

	q->items[q->head++] = item;

	return 1;
}

void *dequeue(struct queue *q) {
	uint8_t tail = q->tail;
	uint8_t head = q->head;

	if (tail + 1 > head) {
		return NULL;
	}

	return q->items[q->tail++];
}

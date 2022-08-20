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

static inline int __attribute__((always_inline)) 
	enqueue_from_isr(volatile struct queue *q, volatile void *itm) {
	
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

static inline void *__attribute__((always_inline)) 
	dequeue_from_isr(volatile struct queue *q) {
	
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

static inline int __attribute__((always_inline)) 
	queue_is_empty_from_isr(volatile struct queue *q) {
	return (q->size == 0);
}

static inline int __attribute__((always_inline)) 
	queue_is_full_from_isr(volatile struct queue *q) {
	return (q->capacity <= q->size);
}

int enqueue(struct queue *q, void *itm);

void *dequeue(struct queue *q);

int queue_is_empty(struct queue *q);

int queue_is_full(struct queue *q);

#endif

#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

Queue* queue(size_t size, size_t maxnitems)
{
	if (maxnitems > QUEUE_MAX_SIZE){
		return NULL;
	}
	Queue *q = malloc(sizeof(Queue));
	if (!q) {
		return NULL;
	}
	q->Q = malloc(maxnitems * size);
	if (!q->Q){
		return NULL;
	}
	q->size = size;
	q->head = 0;
	q->tail = 0;
	q->maxnitems = maxnitems;
	q->nitems = 0;
	return q;
}

bool is_queue_empty(Queue *q)
{
	return q->nitems == 0;
}

int enqueue(Queue *q, void *x)
{
	if (q->nitems == q->maxnitems) {
		return -1;
	}
	q->tail = is_queue_empty(q) ?
		q->tail : (q->tail + 1) % q->maxnitems;
	q->nitems++;
	void* index = q->Q + q->tail * q->size;
	memcpy(index, x, q->size);
	return 0;
}

void * dequeue(Queue * q, void *f(void *))
{
	if (is_queue_empty(q)){
		return NULL;
	}
	size_t old_head = q->head;
	q->nitems--;
	q->head = is_queue_empty(q) ?
		q->head : (q->head + 1) % q->maxnitems;
	return f(q->Q + old_head * q->size);
}

void delQueue(Queue *q)
{
	free(q->Q);
	free(q);
}

void print_queue(Queue *q, const char msg[])
{
	printf("%s:", msg);
	printf(" maxnitems: %zu, nitems: %zu, size: %zu, head: %zu, tail: %zu\n", q->maxnitems,q->nitems, q->size, q->head, q->tail);
}

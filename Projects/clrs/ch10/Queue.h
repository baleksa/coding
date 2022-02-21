#include <stddef.h>
#include <stdbool.h>

#define QUEUE_MAX_SIZE 10000

typedef struct {
	void *Q;
	size_t size;
	size_t tail, head;
	size_t nitems;
	size_t maxnitems;
}Queue;

Queue* queue(size_t, size_t);
bool is_queue_empty(Queue *);
int enqueue(Queue *, void *);
void * dequeue(Queue *, void *(void *));
void delQueue(Queue *);
void print_queue(Queue *, const char []);

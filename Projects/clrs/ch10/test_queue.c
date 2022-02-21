#include "Queue.h"
#include <stdio.h>

void *f(void *ptr)
{
	if (!ptr){
		return NULL;
	}
	return (int *)ptr;
}

void print_qelements(Queue *q)
{
	printf("q el:");
	for (size_t i = 0; i < q->nitems; i++){
		printf(" %d", *(int *)(q->Q + ((q->head + i) % q->maxnitems) * q->size));
	}
	printf("\n");
}

int get_el(int *ptr)
{
	return *ptr;
}

int main (int argc, char *argv[])
{
	Queue *q = queue(sizeof(int), 10);	
	print_queue(q, "after initialization");
	int x = 1;
	enqueue(q, &x);
	x = 2;
	enqueue(q, &x);
	x = 3;
	enqueue(q, &x);
	print_qelements(q);
	print_queue(q, "with 3 el");
	int dq = get_el(dequeue(q, f));
	x = 17;
	print_qelements(q);
	enqueue(q, &x);
	print_qelements(q);
	printf("this should be 1: %d\n" , dq);
	print_queue(q, "head should be 1, tail 0");
	return 0;
}

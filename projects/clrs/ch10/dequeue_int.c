#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_DEQ_SIZE 1000

typedef struct {
	size_t size;	
	size_t len;
	int *dq;
	size_t head, tail;
} dequeue; 

dequeue * Dq(size_t size)
{
	dequeue *dq = malloc(size * sizeof(dequeue));
	dq->size = size;
	dq->dq = malloc(dq->size * sizeof(int));
	dq->head = size / 2;
	dq->tail = size / 2;
	dq->len = 0;
	return dq;
}

int push_head(dequeue *dq, int x)
{
	if (dq->len == MAX_DEQ_SIZE)
		return -1;
	dq->head = dq->len ? (dq->head - 1 + dq->size) % dq->size : dq->head;
	dq->dq[dq->head] = x;
	dq->len++;
	return 0;
}

int pop_head(dequeue *dq)
{
	if (dq->len == 0) {
		return -1;
	}
	int val = dq->dq[dq->head];
	dq->head = dq->len == 1 ? dq->head : (dq->head + 1) % dq->size;
	dq->len--;
	return val;
}


int push_tail(dequeue *dq, int x)
{
	if (dq->len == MAX_DEQ_SIZE)
		return -1;
	dq->tail = dq->len ? (dq->tail + 1) % dq->size : dq->tail;
	// printf("push_tail %d\n", x);
	dq->dq[dq->tail] = x;
	dq->len++;
	return 0;
}

int pop_tail(dequeue *dq)
{
	if (dq->len == 0) {
		return -1;
	}
	int val = dq->dq[dq->tail];
	dq->tail = dq->len == 1 ? dq->tail : (dq->tail - 1 + dq->size) % dq->size;
	dq->len--;
	return val;
}


void print_dq(dequeue *dq, char *msg)
{
	printf("%s:", msg);
	printf(" len=%zu size=%zu head=%zu tail=%zu\n", dq->len, dq->size, dq->head, dq->tail);
	printf("in dq:");
	for(int i = 0; i < dq->len; i++){
		printf(" %d", dq->dq[(dq->head + i) % dq->size]);
	}
	printf("\n");
}

int main (int argc, char *argv[])
{
	size_t size = 3;
	dequeue *dq = Dq(size);	
	print_dq(dq, "after init");
	push_head(dq, 10);
	push_head(dq, 10);
	push_head(dq, 10);
	print_dq(dq, "after 3 push_head");
	int x = pop_head(dq);
	print_dq(dq, "after 1 pop_head");
	printf("popped=%d\n", x);
	x = pop_head(dq);
	print_dq(dq, "after 2 pop_head");
	printf("popped=%d\n", x);
	x = pop_head(dq);
	print_dq(dq, "after 3 pop_head");
	printf("popped=%d\n", x);
	pop_head(dq);
	print_dq(dq, "after empty pop_head");
	pop_head(dq);
	print_dq(dq, "after empty pop_head");
	pop_head(dq);
	print_dq(dq, "after empty pop_head");
	pop_head(dq);
	print_dq(dq, "after empty pop_head");

	return 0;
}

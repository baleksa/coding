#include "List.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct listq {
  list *head;
  list *tail;
  size_t size;
} listq;

int *get_key_ptr(list *ln) { return (int *)(ln->key); }

list *make_lnode(int key) {
  list *node = malloc(sizeof(list));
  node->key = malloc(sizeof(int));
  node->next = NULL;
  *get_key_ptr(node) = key;
  return node;
}

void print_list(list *ln, const char *msg) {
  printf("%s:", msg);
  for (list *node = ln; node; node = node->next) {
    printf(" %d", *get_key_ptr(node));
  }
  printf("\n");
}

list *deq(listq *q) {
  if (!q || !q->head || !q->size) {
    return NULL;
  }
  list *node = q->head;
  q->head = q->head->next;
  q->size--;
  if (!q->size) {
    q->tail = NULL;
  }
  return node;
}

void enq(listq *q, list *x) {
  if (q->size) {
    q->tail->next = x;
    q->tail = x;
    q->size++;
    return;
  }
  q->head = q->tail = x;
  q->size = 1;
}

void print_listq(listq *lq, char *msg)
{
  printf("%s:", msg);
  printf(" head=%p tail=%p size=%zu\n", lq->head, lq->tail, lq->size);
}

int main(int argc, char *argv[]) {
  listq test = {NULL, NULL, 0};
  listq *q = &test;
  print_listq(q, "empty lq");
  enq(q, make_lnode(1));
  print_listq(q, "lq with 1 item");
  enq(q, make_lnode(2));
  print_listq(q, "lq with 2 item");
  enq(q, make_lnode(3));
  print_listq(q, "lq with 3 item");
  print_list(q->head, "q 1 2 3");
  printf("deq in a row 1 2 3:\n");
  printf("%d\n", *get_key_ptr(deq(q)));
  printf("%d\n", *get_key_ptr(deq(q)));
  print_listq(q, "with 1 item");
  print_list(q->head, "one item");
  printf("%d\n", *get_key_ptr(deq(q)));
  print_listq(q, "lq with 0 item");
  list *popped = deq(q);
  popped = deq(q);
  popped = deq(q);
  popped = deq(q);
  if (!popped) {
    printf("IS NULL\n");
  }
  enq(q, make_lnode(4));
  print_listq(q, "lq with 1 item");
  print_list(q->head, "only 4");
  enq(q, make_lnode(5));
  print_listq(q, "lq with 2 item");
  print_list(q->head, "q with 4 5");
  return 0;
}

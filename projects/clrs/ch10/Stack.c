#include "Stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Stack *stack(size_t size, size_t maxnitems) {
  if (maxnitems > STACK_MAX_SIZE) {
    return NULL;
  }
  Stack *s = malloc(sizeof(Stack));
  if (!s) {
    return NULL;
  }
  s->nitems = 0;
  s->size = size;
  s->maxnitems = maxnitems;
  s->S = malloc(s->maxnitems * s->size);
  return s;
}

void delStack(Stack *S) {
  free(S->S);
  free(S);
}

bool is_stack_empty(Stack *S) { return S->nitems == 0; }

int push(Stack *S, void *x) {
  if (S->nitems == S->maxnitems)
    return -1;
  // printf("S: %u size: %d nitems: %d\n", S->S, S->size, S->nitems);
  // printf("Adress for new item: %u\n", S->S + S->nitems * S->size);
  memcpy(S->S + S->nitems * S->size, x, S->size);
  S->nitems++;
  return 0;
}

void *pop(Stack *S, void *f(void *)) {
  if (is_stack_empty(S))
    return NULL;
  S->nitems--;
  return f(S->S + S->size * S->nitems);
}

void *top(Stack *S, void *f(void *)) {
  if(is_stack_empty(S)) {
    return NULL;
  }
  return f(S->S + S->size * (S->nitems - 1));
}

void print_Stack(Stack *S, const char msg[]) {
  printf("%s:", msg);
  printf(" element size=%zu nitems=%zu\n", S->size, S->nitems);
}

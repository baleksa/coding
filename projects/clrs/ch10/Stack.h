#include <stdbool.h>
#include <stddef.h>
#define STACK_MAX_SIZE 10000

typedef struct Stack {
  void *S;
  size_t size;
  size_t nitems;
  size_t maxnitems;
} Stack;

Stack *stack(size_t, size_t);
bool is_stack_empty(Stack *);
int push(Stack *, void *);
void *pop(Stack *, void *(void *));
void *top(Stack *, void *(void *));
void delStack(Stack *);
void print_Stack(Stack *, const char[]);

#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *get_key_ptr(list *ln) { return (int *)(ln->key); }

void print_list(list *ln, const char *msg) {
  printf("%s:", msg);
  for (list *node = ln; node; node = node->next) {
    printf(" %d", *get_key_ptr(node));
  }
  printf("\n");
}

list *make_lnode(int key) {
  list *node = malloc(sizeof(list));
  node->key = malloc(sizeof(int));
  node->next = NULL;
  *get_key_ptr(node) = key;
  return node;
}

list *pop_from_list(list **head) {
  if (!head) {
    return NULL;
  }
  list *popped = *head;
  *head = (*head)->next;
  return popped;
}

int main(int argc, char *argv[]) {
  list *head_stack = NULL;
  head_stack = list_insert(head_stack, make_lnode(1));
  head_stack = list_insert(head_stack, make_lnode(2));
  head_stack = list_insert(head_stack, make_lnode(3));
  print_list(head_stack, "with 3");
  list_delete(&head_stack, head_stack);
  print_list(head_stack, "without 3");
  return 0;
}

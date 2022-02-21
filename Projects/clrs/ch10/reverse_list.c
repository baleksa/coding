#include "List.h"
#include <stdlib.h>
#include <stdio.h>

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

list *reverse_list(list *l)
{
  if (!l || !l->next){
    return l;
  }
  list *prev = l, *node = l->next;
  prev->next = NULL;
  while (node) {
    list *next = node->next;
    node->next = prev;
    prev = node;
    node = next;
  }
  return prev;
}

int main (int argc, char *argv[])
{
  list *head = NULL;
  head = list_insert(head, make_lnode(1));
  head = list_insert(head, make_lnode(2));
  head = list_insert(head, make_lnode(3));
  head = list_insert(head, make_lnode(4));
  head = list_insert(head, make_lnode(5));
  head = list_insert(head, make_lnode(6));
  print_list(head, "list");
  head = reverse_list(head);
  print_list(head, "list reversed");
  return 0;
}


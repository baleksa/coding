#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A XOR (A XOR C ) = C

typedef struct xor_double_list {
  int key;
  struct xor_double_list *np;
} xor_double_list;

typedef struct {
  xor_double_list *head;
  xor_double_list *tail;
} xor_List;

xor_double_list *make_node(int key) {
  xor_double_list *node = malloc(sizeof(*node));
  node->key = key;
  node->np = NULL;
  return node;
}

int insert_node(xor_List *list, int key) {
  xor_double_list *node = make_node(key);
  if (!list->head) {
    list->head = list->tail = node;
    return 0;
  }
  node->np = list->head;
  list->head->np =
      (xor_double_list *)((unsigned long)node ^ (unsigned long)list->head->np);
  list->head = node;
  return 0;
}

xor_double_list *get_next(xor_double_list *prev, xor_double_list *x) {
  return (xor_double_list *)((unsigned long)prev ^ (unsigned long)x->np);
}

xor_double_list * xor (xor_double_list * y, xor_double_list *x) {
  return (xor_double_list *)((unsigned long)y ^ (unsigned long)x);
}

void print_xor_list(xor_List *list, const char *msg) {
  printf("%s:", msg);
  if (!list->head) {
    printf("\n");
    return;
  }
  xor_double_list *head = list->head;
  xor_double_list *p = NULL;
  xor_double_list *x = head;
  while (x != list->tail) {
    printf("\n%p %d", x, x->key);
    xor_double_list *tmp = x;
    x = get_next(p, x);
    p = tmp;
  }
  printf("\n%p %d", x, x->key);
  printf("\ntail->np: %p", x->np);
  printf("\n");
}

void reverse_xor_list(xor_List *l) {
  xor_double_list *tmp = l->head;
  l->head = l->tail;
  l->tail = tmp;
}

xor_double_list *delete_from_xor_list(xor_List *l, int key) {
  if (!l || !l->head) {
    return NULL;
  }
  if (l->head->key == key) {
    xor_double_list *deleted = l->head;
    if (l->head == l->tail) {
      l->head = l->tail = NULL;
      return deleted;
    }
    xor_double_list *next = get_next(NULL, l->head);
    next->np = get_next(l->head, next);
    l->head = next;
    return deleted;
  }
  xor_double_list *prev = l->head;
  xor_double_list *node = get_next(NULL, l->head);
  xor_double_list *next;
  while (node) {
    next = get_next(prev, node);
    printf("prev=%p node=%p next=%p node->key=%d\n", prev, node, next, node->key);
    if (node->key == key) {
      prev->np = xor(get_next(node, prev), next);
      if (next) {
        next->np = xor(prev, get_next(node, next));
      } else {
        l->tail = prev;
      }
      return node;
    } else {
      prev = node;
    }
    node = next;
  }
  return NULL;
}

void test_print(xor_List *list) {
  xor_double_list *head = list->head;
  xor_double_list *tail = list->tail;
  printf("head: %p\n", head);
  printf("head->np: %p\n", head->np);
  printf("tail: %p\n", tail);
  printf("tail->np: %p\n", tail->np);
  printf("head next: %p\n", get_next(NULL, head));
  printf("tail next: %p\n", get_next(NULL, tail));
}

int main(int argc, char *argv[]) {
  xor_List list_struct = {NULL, NULL};
  xor_List *list = &list_struct;
  print_xor_list(list, "empty list");
  insert_node(list, 0);
  print_xor_list(list, "list 0");
  delete_from_xor_list(list, 0);
  print_xor_list(list, "empty list after deletion");
  insert_node(list, 1);
  insert_node(list, 2);
  insert_node(list, 3);
  insert_node(list, 4);
  insert_node(list, 5);
  print_xor_list(list, "5 4 3 2 1");
  delete_from_xor_list(list, 3);
  print_xor_list(list, "after deletion of 3");
  delete_from_xor_list(list, 1);
  print_xor_list(list, "after deletion of tail 1");
  delete_from_xor_list(list, 5);
  print_xor_list(list, "after deletion of tail 5");
  return 0;
}

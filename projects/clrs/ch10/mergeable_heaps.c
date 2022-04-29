#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lnode_t {
  struct lnode_t *next;
  int key;
} lnode_t;

lnode_t *make_lnode(int key) {
  lnode_t *node = malloc(sizeof(lnode_t));
  node->key = key;
  node->next = NULL;
  return node;
}

void insert_in_sorted_list(lnode_t **list, lnode_t *x) {
  if (!list) {
    return;
  }
  lnode_t *head = *list;
  if (!head) {
    *list = x;
    return;
  }

  if (head->key == x->key) {
    return;
  }

  if (head->key > x->key) {
    x->next = head;
    *list = x;
    return;
  }

  while (head->next && head->next->key < x->key) {
    head = head->next;
  }

  if (head->next && head->next->key == x->key) {
    return;
  }

  x->next = head->next;
  head->next = x;
}

lnode_t *pop_min_from_sorted_list(lnode_t **list) {
  if (!list || !*list) {
    return NULL;
  }
  lnode_t *head = *list;
  *list = head->next;
  return head;
}

int get_min_from_sorted_list(lnode_t *head) { return head ? head->key : -1; }

void insert_in_unsorted_list(lnode_t **list, lnode_t *x) {
  if(!list) {
    return;
  }
  lnode_t *head = *list;
  if(!head) {
    *list = x;
    return;
  }
  lnode_t *prev = NULL;
  while (1) {
    while (head && head->key < x->key) {
      prev = head;
      head = head->next;
    }
    if (!head) {
      prev->next = x;
      return;
    } else if (head->key == x->key) {
      return;
    }
    int tmp = head->key;
    head->key = x->key;
    x->key = tmp;
  }
}

void print_list(lnode_t *head, const char *msg) {
  printf("%s:", msg);
  for (; head; head = head->next) {
    printf(" %d", head->key);
  }
  printf("\n");
}

lnode_t *union_two_sorted_lists(lnode_t *head1, lnode_t *head2) {
  lnode_t merged_list_dummy;
  lnode_t *tmp = &merged_list_dummy;
  while (head1 && head2) {
    if (head1->key < head2->key) {
      tmp->next = head1;
      head1 = head1->next;
    } else if (head1->key > head2->key) {
      tmp->next = head2;
      head2 = head2->next;
    } else {
      tmp->next = head1;
      head1 = head1->next;
      head2 = head2->next;
    }
    tmp = tmp->next;
  }
  if (head1) {
    tmp->next = head1;
  } else {
    tmp->next = head2;
  }
  return merged_list_dummy.next;
}

void test_sorted_list() {
  lnode_t *head1 = NULL;
  insert_in_sorted_list(&head1, make_lnode(0));
  insert_in_sorted_list(&head1, make_lnode(3));
  insert_in_sorted_list(&head1, make_lnode(3));
  insert_in_sorted_list(&head1, make_lnode(1));
  insert_in_sorted_list(&head1, make_lnode(5));
  insert_in_sorted_list(&head1, make_lnode(-3));
  print_list(head1, "first list");
  lnode_t *head2 = NULL;
  insert_in_sorted_list(&head2, make_lnode(-2));
  insert_in_sorted_list(&head2, make_lnode(6));
  insert_in_sorted_list(&head2, make_lnode(2));
  insert_in_sorted_list(&head2, make_lnode(6));
  insert_in_sorted_list(&head2, make_lnode(5));
  insert_in_sorted_list(&head2, make_lnode(-4));
  print_list(head2, "second list");
  lnode_t *merged_list = union_two_sorted_lists(head1, head2);
  print_list(merged_list, "merged lists");
}

void test_unsorted_list() {

}

int main(int argc, char *argv[]) {
  test_sorted_list();
  return 0;
}

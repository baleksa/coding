#include <stdlib.h>
#include <string.h>

list *list_search(list *l, void *k, size_t size) {
  list *x = l;
  while (x && memcmp(x->key, k, size))
    x = x->next;
  return x;
}

dlist *dlist_search(dlist *l, void *k, size_t size) {
  dlist *x = l->next;
  while (x && memcmp(x->key, k, size))
    x = x->next;
  return x;
}

slist *slist_search(slist *nill, void *k, size_t size) {
  slist *x = nill->next;
  while (x != nill && memcmp(x->key, k, size))
    x = x->next;
  return x;
}

list *list_insert(list *l, list *x) {
  x->next = l;
  return x;
}

dlist *dlist_insert(dlist *l, dlist *x) {
  x->next = l;
  if (l)
    l->prev = x;
  return x;
}

void slist_insert(slist *nill, slist *x) {
  x->next = nill->next;
  x->prev = nill;
  nill->next->prev = x;
  nill->next = x;
}

list *list_delete_next(list *prev) {
  if (!prev || !prev->next)
    return NULL;
  list *deleted = prev->next;
  prev->next = prev->next->next;
  return prev->next;
}

list *list_delete(list **head, list *x) {
  if (!x || !head || !*head) {
    return NULL;
  }
  list *l = *head;
  if (l == x) {
    *head = l->next;
    return l;
  }
  list *node = l;
  while (node && node->next != x) {
    node = node->next;
  }
  if (node) {
    list_delete_next(node);
  }
  return NULL;
}

dlist *dlist_delete(dlist *dl, dlist *x) {
  if (!dl)
    return NULL;
  if (!x)
    return dl;
  if (x->next) {
    x->next->prev = x->prev;
  }
  if (x->prev) {
    x->prev->next = x->next;
    return dl;
  } else {
    return x->next;
  }
}

void slist_delete(slist *x) {
  if (!x) {
    return;
  }
  x->prev->next = x->next;
  x->next->prev = x->prev;
}

void del_dnode(dlist *x) {
  if (!x) {
    return;
  }
  free(x->key);
  free(x);
}
void del_lnode(list *x) {
  if (!x) {
    return;
  }
  free(x->key);
  free(x);
}
void del_snode(slist *x) {
  if (!x) {
    return;
  }
  free(x->key);
  free(x);
}

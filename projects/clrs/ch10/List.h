#include <stddef.h>

typedef struct list {
  void *key;
  struct list *next;
} list;

typedef struct slist {
  void *key;
  struct slist *next;
  struct slist *prev;
} slist;

typedef struct dlist {
  void *key;
  struct dlist *next;
  struct dlist *prev;
} dlist;

list *lnode(void *, size_t);
dlist *dnose(void *, size_t);
slist *snode(void *, size_t);

list *list_search(list *, void *, size_t);
dlist *dlist_search(dlist *, void *, size_t);
slist *slist_search(slist *, void *, size_t);
list *list_insert(list *, list *);
dlist *dlist_insert(dlist *, dlist *);
void slist_insert(slist *, slist *);
list *list_delete_next(list *);
list *list_delete(list **, list *);
void slist_delete(slist *);
dlist *dlist_delete();
void del_lnode(list *);
void del_dnode(dlist *);
void del_snode(slist *);

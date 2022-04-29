#include <stdio.h>
#include <stdlib.h>

typedef struct tnode_t {
  int key;
  struct tnode_t *left, *right, *parent;
} tnode_t;

tnode_t *make_tnode(int);
void del_tree(tnode_t *);
tnode_t *search_tree(tnode_t *, int);
tnode_t *search_tree_iterative(tnode_t *, int);
tnode_t *get_tree_minimum(tnode_t *);
tnode_t *get_tree_maximum(tnode_t *);
tnode_t *get_node_successor(tnode_t *);
tnode_t *get_node_predecessor(tnode_t *);

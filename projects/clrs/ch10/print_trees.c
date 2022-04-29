#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

#define N 3

typedef struct ntnode_t {
  int key;
  struct ntnode_t *children[N];
} ntnode_t;

typedef struct atnode_t {
  int key;
  struct atnode_t *child, *first_sibling;
} atnode_t;

typedef struct btnode_t {
  int key;
  struct btnode_t *parent, *left, *right;
} btnode_t;

btnode_t *make_btnode(int key) {
  btnode_t *node = malloc(sizeof(btnode_t));
  node->key = key;
  node->parent = NULL;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void print_ntree_recursive_(ntnode_t *root, int nchildren) {
  if (!root) {
    return;
  }
  printf("%d ", root->key);
  for (int i = 0; i < nchildren; i++) {
    print_ntree_recursive_(root->children[i], nchildren);
  }
}

void print_ntree_recursive(ntnode_t *root, int nchildren) {
  print_ntree_recursive_(root, nchildren);
  printf("\n");
}
void *f(void *ptr) { return *(ntnode_t **)ptr; }

void print_ntree_nonrecursive(ntnode_t *root, int nchildren) {
  if (!root) {
    return;
  }
  Stack *nodes = stack(sizeof(ntnode_t *), 100000);
  push(nodes, &root);
  while (nodes->nitems) {
    ntnode_t *tmp = (ntnode_t *)pop(nodes, f);
    printf("%d ", tmp->key);
    for (int i = 0; i < nchildren; i++) {
      if (tmp->children[i]) {
        push(nodes, tmp->children + i);
      }
    }
  }
  delStack(nodes);
  printf("\n");
}

void print_btree_nonrecursive_constant_space(btnode_t *root) {
  if (!root) {
    return;
  }
  btnode_t *prev = NULL, *x = root;
  while (x) {
    // printf("prev=%p x=%p parent=%p left=%p right=%p\n", prev, x, x->parent,
    //        x->left, x->right);
    if (prev == x->parent) {
      printf("%d ", x->key);
      prev = x;
      if (x->left) {
        x = x->left;
      } else if (x->right) {
        x = x->right;
      } else {
        x = x->parent;
      }
    } else if (prev == x->left && x->right) {
      // if (x->right) {
      prev = x;
      x = x->right;
      // } else {
      //   prev = x;
      //   x = x->parent;
      // }
    } else { // if (prev == x->right) {
      prev = x;
      x = x->parent;
    }
  }
  printf("\n");
}

void print_atree_recursive_(atnode_t *root) {
  if (!root) {
    return;
  }
  atnode_t *node = root;
  while (node) {
    printf("%d ", node->key);
    node = node->first_sibling;
  }
  print_atree_recursive_(root->child);
}

void print_atree_recursive(atnode_t *root) {
  print_atree_recursive_(root);
  printf("\n");
}

void *f2(void *ptr) { return *(atnode_t **)ptr; }

void print_atree_nonrecursive(atnode_t *root) {
  if (!root) {
    return;
  }
  Stack *nodes = stack(sizeof(atnode_t *), 10000);
  push(nodes, &root);
  while (nodes->nitems) {
    atnode_t *tmp = pop(nodes, f2);
    if (tmp->child) {
      push(nodes, &(tmp->child));
    }
    while (tmp) {
      printf("%d ", tmp->key);
      tmp = tmp->first_sibling;
    }
  }
  delStack(nodes);
  printf("\n");
}

ntnode_t *make_ntnode(int key, int nchildren) {
  ntnode_t *node = malloc(sizeof(ntnode_t));
  node->key = key;
  for (int i = 0; i < nchildren; i++) {
    node->children[i] = NULL;
  }
  return node;
}

atnode_t *make_atnode(int key) {
  atnode_t *node = malloc(sizeof(atnode_t));
  node->key = key;
  node->child = NULL;
  node->first_sibling = NULL;
  return node;
}

void test_ntree() {
  ntnode_t *root = make_ntnode(0, N);
  root->children[0] = make_ntnode(1, N);
  root->children[1] = make_ntnode(2, N);
  print_ntree_recursive(root, N);
  print_ntree_nonrecursive(root, N);
}

void test_atree() {
  atnode_t *root = make_atnode(0);
  root->child = make_atnode(1);
  root->child->first_sibling = make_atnode(2);
  root->child->child = make_atnode(3);
  print_atree_recursive(root);
  print_atree_nonrecursive(root);
}

void test_btree() {
  btnode_t *root = make_btnode(0);
  root->left = make_btnode(1);
  root->left->parent = root;
  root->right = make_btnode(2);
  root->right->parent = root;
  root->left->left = make_btnode(3);
  root->left->left->parent = root->left;
  root->right->left = make_btnode(4);
  root->right->left->parent = root->right;
  // root->right = make_btnode(2);
  print_btree_nonrecursive_constant_space(root);
}

int main(int argc, char *argv[]) {
  test_btree();
  return 0;
}

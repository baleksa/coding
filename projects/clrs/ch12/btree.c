#include "btree.h"
#include <stdlib.h>

tnode_t *make_tnode(int key) {
  tnode_t *node = malloc(sizeof(tnode_t));
  node->key = key;
  node->left = node->right = node->parent = NULL;
  return node;
}

void del_tree(tnode_t *root) {
  if (!root) {
    return;
  }
  del_tree(root->left);
  del_tree(root->right);
  free(root);
}

tnode_t *search_tree(tnode_t *root, int x) {
  if (!root || root->key == x) {
    return root;
  } else if (x < root->key) {
    return search_tree(root->left, x);
  } else { // x > root->key
    return search_tree(root->right, x);
  }
}

tnode_t *search_tree_iterative(tnode_t *root, int x) {
  while (root && root->key != x) {
    if (x < root->key) {
      root = root->left;
    } else if (x > root->key) {
      root = root->right;
    }
  }
  return root;
}

tnode_t *get_tree_minimum(tnode_t *root) {
  while (root->left) {
    root = root->left;
  } 
  return root;
}

tnode_t *get_tree_maximum(tnode_t *root) {
  while (root->right) {
    root = root->right;
  } 
  return root;
}

tnode_t *get_node_successor(tnode_t *x) {
  if (x->right) {
    return get_tree_minimum(x->right);
  }
  tnode_t *next = x->parent;
  while (next && x == next->right) {
    x = next;
    next = next->parent;
  }
  return next;
}

tnode_t *get_node_predecessor(tnode_t *x) {
  if (x->left) {
    return get_tree_maximum(x->left);
  }
  tnode_t *next = x->parent;
  while (next && x == next->left) {
    x = next;
    next = next->parent;
  }
  return next;
}

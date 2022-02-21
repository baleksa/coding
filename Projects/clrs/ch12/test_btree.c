#include "../ch10/Stack.h"
#include "btree.h"
#include <stdio.h>
#include <stdlib.h>

void inorder_btree_walk_(tnode_t *root) {
  if (!root) {
    return;
  }
  inorder_btree_walk_(root->left);
  printf("%d ", root->key);
  inorder_btree_walk_(root->right);
}

void inorder_btree_walk(tnode_t *root) {
  inorder_btree_walk_(root);
  printf("\n");
}

void test_tree() {
  tnode_t *root = make_tnode(10);
  tnode_t *n2 = make_tnode(4);
  n2->parent = root;
  root->left = n2;
  tnode_t *n4 = make_tnode(1);
  n4->parent = n2;
  n2->left = n4;
  tnode_t *n5 = make_tnode(5);
  n5->parent = n2;
  n2->right = n5;
  tnode_t *n3 = make_tnode(17);
  n3->parent = root;
  root->right = n3;
  tnode_t *n6 = make_tnode(16);
  n6->parent = n3;
  n3->left = n6;
  tnode_t *n7 = make_tnode(21);
  n7->parent = n3;
  n3->right = n7;
  tnode_t *n15 = make_tnode(26);
  n15->parent = n7;
  n7->right = n15;
  tnode_t *n8 = make_tnode(0);
  n4->left = n8;
  n8->parent = n4;
  tnode_t *n14 = make_tnode(18);
  n7->left = n14;
  n14->parent = n7;
  inorder_btree_walk(root);
  int key = 18;
  tnode_t *found = search_tree_iterative(root, key);
  printf("search %d: %p->key=%d\n", key, found, found ? found->key : -1);
  printf("tree miminum: %d\n", get_tree_minimum(root)->key);
  printf("tree maximum: %d\n", get_tree_maximum(root)->key);
  tnode_t *current = n4;
  printf("pre=%d key=%d suc=%d\n", get_node_predecessor(current)->key, current->key,
         get_node_successor(current)->key);
}

int main(int argc, char *argv[]) {
  test_tree();
  return 0;
}

#include "../ch10/Stack.h"
#include "btree.h"
#include <stdio.h>
#include <stdlib.h>

void *get_val_from_stack(void *ptr) { return *(tnode_t **)ptr; }

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

void inorder_btree_walk_with_stack(tnode_t *root) {
  if (!root) {
    return;
  }
  Stack *nodes = stack(sizeof(tnode_t *), 1000);

  tnode_t *node = root;
  while (true) {
    if (node) {
      push(nodes, &node);
      node = node->left;
    } else {
      if (is_stack_empty(nodes)) {
        break;
      }
      node = pop(nodes, get_val_from_stack);
      printf("%d ", node->key);
      node = node->right;
    }
  }
  printf("\n");
}

void inorder_btree_walk_with_two_ptrs(tnode_t *root) {
  if (!root) {
    return;
  }
  tnode_t *current = root, *pre = NULL;
  while (current) {
    if (pre == current->parent) {
      pre = current;
      if (current->left) {
        current = current->left;
      } else {
        printf("%d ", current->key);
        if (current->right) {
          current = current->right;
        } else {
          current = current->parent;
        }
      }
    } else if (pre == current->left) {
      printf("%d ", current->key);
      pre = current;
      if (current->right) {
        current = current->right;
      } else {
        current = current->parent;
      }
    } else {
      pre = current;
      current = current->parent;
    }
  }
  printf("\n");
}

void preorder_btree_walk_(tnode_t *root) {
  if (!root) {
    return;
  }
  printf("%d ", root->key);
  preorder_btree_walk_(root->left);
  preorder_btree_walk_(root->right);
}

void preorder_btree_walk(tnode_t *root) {
  preorder_btree_walk_(root);
  printf("\n");
}

void postorder_btree_walk_(tnode_t *root) {
  if (!root) {
    return;
  }
  postorder_btree_walk_(root->left);
  postorder_btree_walk_(root->right);
  printf("%d ", root->key);
}
void postorder_btree_walk(tnode_t *root) {
  postorder_btree_walk_(root);
  printf("\n");
}

void test_inorder_stack() {
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
  inorder_btree_walk_with_stack(root);
  inorder_btree_walk_with_two_ptrs(root);
}

int main(int argc, char *argv[]) {
  test_inorder_stack();
  return 0;
}

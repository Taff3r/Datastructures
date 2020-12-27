#ifndef BST_H
#define BST_H
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <assert.h>
typedef struct bst_node bst_node;

/*
 * Binary Search Tree (As a set)
 */
struct bst_node {
  int el;
  unsigned int inserted;
  bst_node *left, *right;
};

/* Creates a new BST node
 * Left and right pointers are set to NULL.
 * Element is set to INT_MIN as a placeholder.
 */
bst_node* new_bst()
{
  bst_node* root;
  if ((root = (bst_node*) malloc(sizeof(bst_node)))) {
    root->left = root->right = NULL;
    root->inserted = 0;
    return root;
  }
  return NULL;
}

void delete_bst(bst_node* root) 
{
  if (root == NULL)
    return;
  delete_bst(root->left);
  delete_bst(root->right);
  free(root);
}

/* TODO:
 * Add removal operation
 */
int put(bst_node* cur, int el)
{

  /* Leaf insert */
  if (!cur->inserted) {
    printf("Putting %d at %p\n", el, cur);
    cur->el    = el;
    cur->right = new_bst();
    cur->left  = new_bst();
    cur->inserted = 1;
    return 1;
  }
  /* Otherwise compare and act accordingly */
  if (cur->el > el)
    return put(cur->left, el);
  else if (cur->el < el)
      return put(cur->right, el);
  assert(el == cur->el);
  return 0; /* No duplicates */
}

bst_node* find(bst_node* cur, int el)
{
  if (cur == NULL)
    return NULL; /* Not in the tree */
  if (cur->el == el)
    return cur; /* Found it */
  else if (cur->el > el)
    return find(cur->left, el); /* look to the left */
  else 
    return find(cur->right, el); /* look to the right */
}

int contains(bst_node* root, int el) {
  return find(root, el) != NULL;
}

void _print_node(bst_node* cur, FILE* out)
{
  if (cur == NULL || !cur->inserted)
    return;
  _print_node(cur->left, out);
  fprintf(out, "[%d] ", cur->el);
  _print_node(cur->right, out);
}
/* Prints the elements in the tree in order */
void print_tree(bst_node* root, FILE* out)
{
  fprintf(out, "IN ORDER PRINT:\n");
  _print_node(root, out);
  fprintf(out, "\n");
}
#endif

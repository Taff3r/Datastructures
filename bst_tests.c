#include "bst.h"
#include <assert.h>
#include <stdio.h>
int main(void)
{
  FILE* out = stdout;
  bst_node* root = new_bst();
  put(root, 1);
  print_tree(root, out);
  assert(1 == contains(root, 1));
  assert(0 == contains(root, 2));
  put(root, 2);
  assert(1 == contains(root, 2));
  put(root, -1);
  put(root, 42);
  print_tree(root, out);
  delete_bst(root);
  printf("Done!\n");
}

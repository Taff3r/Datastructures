#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
int main(void)
{
  linked_list* root;
  root = new_linked_list();
  append(root, 1);
  append(root, 2);
  append(root, 3);
  assert(1 == contains(root, 1));
  assert(1 == contains(root, 2));
  assert(1 == contains(root, 3));
  printf("%d\n", root->len);
  assert(3 == root->len);
  assert(2 == ll_remove(root, 1));
  assert(0 == ll_remove(root, 5));
  append(root, 1);
  append(root, 4);
  assert(3 == ll_remove(root, 2));
  append(root, 7);
  FILE* out = stdout;
  print_list(root, out);
  delete_linked_list(root);
  printf("Done!\n");
}

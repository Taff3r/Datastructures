#include "dynarr.h"
#include <assert.h>
#include <stdio.h>
int main(void)
{
  FILE* out = stdout;
  dyn_arr* arr = new_dyn_arr(2);
  append(arr, 2);
  append(arr, 4);
  assert(1 == contains(arr, 2));
  assert(1 == contains(arr, 2));
  assert(0 == contains(arr, 3));
  append(arr, 2);
  append(arr, 3);
  append(arr, 4);
  print_dyn_arr(arr, out);
  set(arr, 1, 0);
  assert(1 == get(arr, 0));
  delete_arr(arr);
  printf("Done!\n");
}

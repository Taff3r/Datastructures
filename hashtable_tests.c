#include "hashtable.h"
#include <assert.h>
#include <stdio.h>
int main(void)
{
  FILE* out = stdout;
  hash_table* table = new_hash_table(10);
  printf("Begin\n");
  put(table, "hello", 10);
  put(table, "yo", -1);
  put(table, "Hej", -1);
  put(table, "Tjenamors!", -1);
  put(table, "Tjenamors!", 10);
  print_table(table, out);
  assert(10 == get(table, "hello"));
  delete_table(table);
  printf("Done!\n");
}

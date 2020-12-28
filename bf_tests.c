#include "bloomfilter.h"
#include <assert.h>
#include <stdio.h>

int main(void)
{
  bloom_filter* bf; 
  FILE* out;
  
  out = stdout;
  bf = new_bloom_filter();
  set_bit(bf->bitfield, 0);
  set_bit(bf->bitfield, 3);

  assert(1 == is_set(bf->bitfield, 0));
  assert(0 == is_set(bf->bitfield, 5));

  toggle(bf->bitfield, 5);
  assert(1 == is_set(bf->bitfield, 5));

  toggle(bf->bitfield, 5);
  assert(0 == is_set(bf->bitfield, 5));

  unset(bf->bitfield, 5);
  assert(0 == is_set(bf->bitfield, 5));

  toggle(bf->bitfield, 5);
  assert(1 == is_set(bf->bitfield, 5));
  
  print_filter(bf, out);
  delete_bloom_filter(bf);
  bf = new_bloom_filter();
  
  put(bf, 10);
  put(bf, 100200121);
  assert(1 == can_contain(bf, 10));
  assert(1 == can_contain(bf, 100200121));
  assert(0 == can_contain(bf, 1));
  delete_bloom_filter(bf);
  printf("Done!\n");
}

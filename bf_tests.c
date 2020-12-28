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
  put(bf, 123);
  put(bf, 7181212);
  put(bf, 123123);

  unsigned int i;
  for (i = 0; i < 100; ++i)
    put(bf, i);

  assert(1 == can_contain(bf, 10));
  assert(1 == can_contain(bf, 100200121));
  print_filter(bf, out);

  for (i = 0; i < 100; ++i)
    assert(1 == can_contain(bf, i));

  assert(0 == can_contain(bf, 101));
  delete_bloom_filter(bf);
  printf("Done!\n");
}

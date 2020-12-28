#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BIT_FIELD_LEN 8 

/*
 * Bloom filter
 * Wikipedia: https://en.wikipedia.org/wiki/Bloom_filter
 * 
 * Can be used to determine if a value is present in a set, by hashing the value through
 * _k_ different hash-functions and obtaining _k_ different indices for the key.
 * Then setting the bits at those positions. 
 *
 * When checking if a value is present the same bits are tested, using good hashing algorithms
 * this can only produce positives and false postivies, never false negatives.
 * I.e. the check can give either the results: "Possibly in the set" or "Certainly not in the set".
 *
 * Deletions are impossible, i.e. the set can only grow.
 * The larger the number of inserts, the higher the probability of a false positive.
 *
 * Some math:
 *  m = number of bits. In this case 32 * BIT_FIELD_LEN
 *  k = number of hash functions
 *  n = number of inserted elements.
 *  Probability of false positive:
 *      P(false positive) = (1 - e^(-kn/m))^k 
 *
 *  Optimal number of hash functions that minimizes the number of false positives:
 *      k = (m/n) * ln(2)
 *
 *
 *  NOTE:
 *    This is only a proof of concept that works on integers, 
 *    for the same datastructures special hash functions need 
 *    to used depending on the value to be inserted.
 */

typedef struct bloom_filter bloom_filter;
struct bloom_filter {
  u_int32_t bitfield[BIT_FIELD_LEN];
};

size_t  _hash1(unsigned int val) {
  val = ((val >> 16) ^ val) * 0x45d9f3b;
  val = ((val >> 16) ^ val) * 0x45d9f3b;
  val = (val >> 16) ^ val;
  return val % (BIT_FIELD_LEN * 32);
}

size_t  _hash2(unsigned int val) {
  val = ((val >> 16) ^ val) * 0xDEADBEEF;
  val = ((val >> 16) ^ val) * 0xDEADBEEF;
  val = (val >> 16) ^ val;
  return val % (BIT_FIELD_LEN * 32);
}

size_t  _hash3(unsigned int val) {
  val = ((val >> 16) ^ val) * 0xFEEDBEEF;
  val = ((val >> 16) ^ val) * 0xFEEDBEEF;
  val = (val >> 16) ^ val;
  return val % (BIT_FIELD_LEN * 32);
}

bloom_filter* new_bloom_filter()
{
  bloom_filter* bf;
  size_t i;
  bf = (bloom_filter*) malloc(sizeof(bloom_filter));
  
  for (i = 0; i < BIT_FIELD_LEN; ++i)
    bf->bitfield[i] = 0x0;
  return bf;
}

void delete_bloom_filter(bloom_filter* bf)
{
  free(bf);
}

void set_bit(u_int32_t field[], unsigned int pos)
{
  unsigned int offset;
  unsigned int flag;

  offset = pos / 32;
  flag   = pos % 32; 
  
  field[offset] |= 0x1 << flag;
}

void put(bloom_filter* bloom_filter, unsigned int val)
{
  size_t b1, b2, b3;
  b1 = _hash1(val);
  b2 = _hash2(val);
  b3 = _hash3(val);
  set_bit(bloom_filter->bitfield, b1);
  set_bit(bloom_filter->bitfield, b2);
  set_bit(bloom_filter->bitfield, b3);
}

void print_filter(bloom_filter* bloom_filter, FILE* out)
{
  size_t i, k;
  for (i = 0; i < BIT_FIELD_LEN; ++i) {
    u_int32_t n;
    n = bloom_filter->bitfield[i];
    fprintf(out, "D: %d B: ", n);
    for (k = 0; k < 32; ++k) {
      fprintf(out, "%x",  (n & (0x1 << k)) >> k);
    }
    fprintf(out, "\n");
  }
  fprintf(out, "\n");
}

int is_set(u_int32_t field[], unsigned int pos)
{
  unsigned int offset;
  unsigned int flag;

  offset = pos / 32;
  flag   = pos % 32; 
  
  return (field[offset] & (0x1 << flag)) != 0;
}

int can_contain(bloom_filter* bloom_filter, unsigned int val)
{
  size_t b1, b2, b3;
  b1 = _hash1(val);
  b2 = _hash2(val);
  b3 = _hash3(val);
  return is_set(bloom_filter->bitfield, b1) && is_set(bloom_filter->bitfield, b2) && is_set(bloom_filter->bitfield, b3);
}
void unset(u_int32_t field[], unsigned int pos)
{
  unsigned int offset;
  unsigned int flag;

  offset = pos / 32;
  flag   = pos % 32; 
  
  field[offset] &= ~(0x1 << flag);
}

void toggle(u_int32_t field[], unsigned int pos)
{
  unsigned int offset;
  unsigned int flag;

  offset = pos / 32;
  flag   = pos % 32; 
  
  field[offset] ^= 0x1 << flag;
}





#endif

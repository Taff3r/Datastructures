#ifndef DYN_ARR_H
#define DYN_ARR_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef struct dyn_arr dyn_arr;
struct dyn_arr {
  int* elements;
  size_t arr_size;
  size_t size;
};


dyn_arr* new_dyn_arr(int size)
{
  dyn_arr* arr = (dyn_arr*) malloc(sizeof(dyn_arr));
  arr->elements = (int*) malloc(size * sizeof(int));
  arr->arr_size = size;
  arr->size = 0;
  return arr;
}

/* Unsafe operation to get an element in the array at index i */
int get(dyn_arr* arr, int i)
{
  return arr->elements[i];
}
/* Unsafe operation to set an element in the array */
void set(dyn_arr* arr, int element, int i) {
  arr->elements[i] = element;
}

/* Doubles the size of the array */
void grow(dyn_arr* arr) {
  int* new_els;
  size_t new_size = arr->arr_size * 2;
  new_els = (int*) malloc(new_size * sizeof(int));
  memcpy(new_els, arr->elements, sizeof(int) * arr->size);
  free(arr->elements);
  arr->elements = new_els;
  arr->arr_size = new_size;
}
void append(dyn_arr* arr, int element) {
  if (arr->size + 1 >= arr->arr_size)
    grow(arr);
  arr->elements[arr->size++] = element;
}

int* start(dyn_arr* arr) {
  return arr->elements;
}

int* end(dyn_arr* arr) {
  return &(arr->elements[arr->size]);
}

int contains(dyn_arr* arr, int element) {
  int* begin;
  int* stop;

  begin  = start(arr);
  stop   = end(arr);

  while (begin != stop) {
    if (*begin == element) 
      return 1;
    ++begin;
  }
  return 0;
}

void print_dyn_arr(dyn_arr* arr, FILE* out) {
  int* begin, *stop;
  begin = start(arr);
  stop  = end(arr);
  while(begin != stop) {
    fprintf(out, "[%d] ", *begin);
    begin++;
  }
  fprintf(out, "\n");
}

void delete_arr(dyn_arr* arr)
{
  free(arr->elements);
  free(arr);
}
#endif

#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>

typedef struct pl_node pl_node;
struct pl_node {
  char* key;
  int el;
  pl_node* next;
};

typedef struct pair_list pair_list;
struct pair_list {
  pl_node *next, *tail;
  size_t len;
};

pair_list* _new_pair_list() {
  pair_list* pl;
  pl = (pair_list*) malloc(sizeof(pair_list));
  pl->next = pl->tail = NULL;
  pl->len = 0;
  return pl;
}

void _delete_pair_list(pair_list* root)
{
  pl_node *next, *curr;
  next = curr = root->next;
  while(1) {
    if (curr == NULL)
      break;
    free(curr->key);
    next = curr->next;
    free(curr);
    curr = next;
  }
  free(root);
}



int contains(pair_list* root, char* key)
{
  pl_node* cur = root->next;
  while(cur != NULL) {
    if (strcmp(cur->key, key) == 0)
      return 1;
    cur = cur->next;
  }
  return 0;
}

pl_node* _find(pair_list* root, char* key)
{
  pl_node* cur = root->next;
  while(cur != NULL) {
    if(strcmp(cur->key, key) == 0)
      return cur;
    cur = cur->next;
  }
  return NULL;
}


int pl_remove(pair_list* root, char* key)
{
  pl_node *last, *cur;

  /* Can't remove something from empty list */
  if (!root->len)
    return 0;

  last = NULL;
  cur  = root->next;
  do  {
    if (strcmp(cur->key, key) == 0) {
      /* Are we are at the first node */
      if (last == NULL) {
        root->next = cur->next;
        if (root->tail == cur)
          root->tail = NULL;
      } else {
        if (cur == root->tail) {
          root->tail = last; /* Make sure the tail points to the last element */ 
        } else 
          last->next = cur->next;
      }
      free(cur);
      return --(root->len);
    }
    last = cur;
  } while(((cur = cur->next)));

  return 0;
}
typedef struct hash_table hash_table;
struct hash_table {
  size_t size;
  pair_list** table;
};

size_t _hash(char* key, hash_table* table)
{
  size_t hash, upper, i;

  upper = strlen(key);
  hash = 0;
  for(i = 0; i < upper; ++i) {
    hash += key[i] * (i + 1);
  }
  
  return hash % table->size;
}

hash_table* new_hash_table(size_t size)
{
  hash_table* t;
  size_t i;

  t = (hash_table*) malloc(sizeof(hash_table));
  t->table = (pair_list**) calloc(size, sizeof(pair_list*));

  for (i = 0; i < size; ++i)
    t->table[i] = _new_pair_list();

  t->size = size;
  return t;
}

void append(pair_list* root, int el, char* key)
{
  if (root->next == NULL) {
    root->next = (pl_node*) malloc(sizeof(pl_node));
    root->next->el = el;
    root->next->key = (char*) malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(root->next->key, key);
    root->next->next = NULL;
    root->tail = root->next;
    root->len++;
    return;
  }
  root->tail->next = (pl_node*) malloc(sizeof(pl_node));
  root->tail->next->el = el;
  root->tail->next->key = (char*) malloc(sizeof(char) * (strlen(key) + 1));
  strcpy(root->tail->next->key, key);
  root->tail = root->tail->next;
  root->tail->next = NULL;
  root->len++;
}

int put(hash_table* t, char* key, int val)
{
  size_t pos;
  pl_node* found;
  pair_list* l;

  pos   = _hash(key, t);
  l     = t->table[pos];
  found = _find(l, key);
  
  if (found)
    found->el = val;
  else 
    append(l, val, key);
  return 0;
}

int get(hash_table* t, char* key)
{
  size_t pos;
  pl_node* found;
  pos = _hash(key, t);

  found = _find(t->table[pos], key);
  if (found)
    return found->el;
  return INT_MIN;
}
void print_pair_list(pair_list* pl, FILE* out)
{
  pl_node* cur = pl->next;
  while(cur) {
    fprintf(out, "{%s : %d}, ", cur->key, cur->el);
    cur = cur->next;
  }
}

void print_table(hash_table* t, FILE* out) 
{
  size_t i;
  for (i = 0; i < t->size; ++i) {
    fprintf(out, "[%ld] -> ", i);
    print_pair_list(t->table[i], out);
    fprintf(out, "\n");
  }
}

void delete_table(hash_table* t)
{
  size_t i;
  for (i = 0; i < t->size; ++i)
    _delete_pair_list(t->table[i]);
  free(t->table);
  free(t);
}
#endif

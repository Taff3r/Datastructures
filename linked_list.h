#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdio.h>
typedef struct linked_list linked_list;
typedef struct ll_node ll_node;
struct ll_node {
  int el;
  ll_node* next;
};

struct linked_list {
  ll_node *next, *tail;
  int len;
};

linked_list* new_linked_list() {
  linked_list* ll;
  if ((ll = (linked_list*) malloc(sizeof(linked_list)))) {
    ll->next = ll->tail = NULL;
    ll->len = 0;
    return ll;
  }
  return NULL;
}

void delete_linked_list(linked_list* root)
{
  ll_node *next, *curr;
  next = curr = root->next;
  while(1) {
    next = curr->next;
    free(curr);
    curr = next;
    if (curr == NULL)
      break;
  }
  free(root);
}

/* TODO Add out of memory check */
void append(linked_list* root, int el)
{
  if (root->next == NULL) {
    root->next = (ll_node*) malloc(sizeof(ll_node));
    root->next->el = el;
    root->next->next = NULL;
    root->tail = root->next;
    root->len++;
    return;
  }
  root->tail->next = (ll_node*) malloc(sizeof(ll_node));
  root->tail->next->el = el;
  root->tail = root->tail->next;
  root->tail->next = NULL;
  root->len++;
}

int contains(linked_list* root, int el)
{
  ll_node* cur = root->next;
  while(cur != NULL) {
    if (cur->el == el)
      return 1;

    cur = cur->next;
  }
  return 0;
}

void print_list(linked_list* root, FILE* out)
{
  fprintf(out, "ROOT -> ");
  ll_node* cur = root->next;
  while(cur != NULL) {
    fprintf(out, "[%d] -> ", cur->el);
    cur = cur->next;
  }
  fprintf(out, "NULL \n");
}

int ll_remove(linked_list* root, int el)
{
  ll_node *last, *cur;

  /* Can't remove something from empty list */
  if (!root->len)
    return 0;

  last = NULL;
  cur  = root->next;
  do  {
    if (cur->el == el) {
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
#endif

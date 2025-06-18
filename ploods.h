// Pointer Linked Organized and Optimized Data Structure
#ifndef PLOODS_H
#define PLOODS_H
#include <stdlib.h>
#include <stdint.h>

#define CREATE_PLOODS(type)                                                                                                       \
                                                                                                                                  \
  typedef struct type##_ploods_node {                                                                                             \
                                                                                                                                  \
    type                       value;                                                                                             \
    struct type##_ploods_node* next;                                                                                              \
    struct type##_ploods_node* prev;                                                                                              \
  } type##_ploods_node;                                                                                                           \
                                                                                                                                  \
  typedef struct type##_ploods {                                                                                                  \
                                                                                                                                  \
    type##_ploods_node* root;                                                                                                     \
    type##_ploods_node* curr;                                                                                                     \
    uint32_t            size;                                                                                                     \
  } type##_ploods;                                                                                                                \
                                                                                                                                  \
  void type##_initialize(type##_ploods* d) {                                                                                      \
    if (d == NULL)                                                                                                                \
      return;                                                                                                                     \
                                                                                                                                  \
    d->size = 0;                                                                                                                  \
                                                                                                                                  \
    d->root = malloc(sizeof(type##_ploods_node));                                                                                 \
    d->curr = d->root;                                                                                                            \
  }                                                                                                                               \
                                                                                                                                  \
  void type##_dispose(type##_ploods* d) {                                                                                         \
    if (d == NULL)                                                                                                                \
      return;                                                                                                                     \
                                                                                                                                  \
    type##_ploods_node* to_delete;                                                                                                \
    while(d->root != NULL) {                                                                                                      \
      to_delete = d->root;                                                                                                        \
      d->root = d->root->next;                                                                                                    \
      free(to_delete);                                                                                                            \
    }                                                                                                                             \
    d->root = NULL;                                                                                                               \
    d->curr = NULL;                                                                                                               \
  }                                                                                                                               \
                                                                                                                                  \
  void type##_make_circular(type##_ploods* d) {                                                                                   \
    if (d == NULL)                                                                                                                \
      return;                                                                                                                     \
                                                                                                                                  \
    d->root->prev = d->curr;                                                                                                      \
    d->curr->next = d->root;                                                                                                      \
  }                                                                                                                               \
                                                                                                                                  \
  type##_ploods_node* type##_get_node(type##_ploods* d, const uint32_t pos) {                                                     \
    if (d == NULL)                                                                                                                \
      return NULL;                                                                                                                \
                                                                                                                                  \
    if (pos + 1 > d->size)                                                                                                        \
      return NULL;                                                                                                                \
                                                                                                                                  \
    type##_ploods_node* trav = d->root;                                                                                           \
    uint32_t i;                                                                                                                   \
    for (i = 0; i < pos; i++)                                                                                                     \
      trav = trav->next;                                                                                                          \
    return trav;                                                                                                                  \
  }                                                                                                                               \
                                                                                                                                  \
  type##_ploods_node* type##_next_node(type##_ploods* d, type##_ploods_node* n) {                                                 \
    if (d == NULL || n == NULL)                                                                                                   \
      return NULL;                                                                                                                \
                                                                                                                                  \
    return n->next;                                                                                                               \
  }                                                                                                                               \
                                                                                                                                  \
  type##_ploods_node* type##_prev_node(type##_ploods* d, type##_ploods_node* n) {                                                 \
    if (d == NULL || n == NULL)                                                                                                   \
      return NULL;                                                                                                                \
                                                                                                                                  \
    return n->prev;                                                                                                               \
  }                                                                                                                               \
                                                                                                                                  \
  type type##_node_value(type##_ploods* d, type##_ploods_node* n) {                                                               \
    if (d == NULL || n == NULL) {                                                                                                 \
      type zero = {0};                                                                                                            \
      return zero;                                                                                                                \
    }                                                                                                                             \
                                                                                                                                  \
    return n->value;                                                                                                              \
  }                                                                                                                               \
                                                                                                                                  \
  void type##_change_node_value(type##_ploods* d, type##_ploods_node* n, const type value) {                                      \
    if (d == NULL || n == NULL)                                                                                                   \
      return;                                                                                                                     \
                                                                                                                                  \
    n->value = value;                                                                                                             \
  }                                                                                                                               \
                                                                                                                                  \
  void type##_insert(type##_ploods* d, const uint32_t pos, const type value) {                                                    \
    if (d == NULL)                                                                                                                \
      return;                                                                                                                     \
                                                                                                                                  \
    if (pos > d->size)                                                                                                            \
      return;                                                                                                                     \
    if (d->size == 0) {                                                                                                           \
      d->root->value = value;                                                                                                     \
                                                                                                                                  \
      d->size++;                                                                                                                  \
                                                                                                                                  \
      return;                                                                                                                     \
    }                                                                                                                             \
    if (pos == 0) {                                                                                                               \
      type##_ploods_node* new_root = malloc(sizeof(type##_ploods_node));                                                          \
      new_root->value = value;                                                                                                    \
      new_root->next = d->root;                                                                                                   \
      d->root->prev = new_root;                                                                                                   \
      d->root = new_root;                                                                                                         \
                                                                                                                                  \
      d->size++;                                                                                                                  \
                                                                                                                                  \
      return;                                                                                                                     \
    }                                                                                                                             \
    if (pos == d->size) {                                                                                                         \
      type##_ploods_node* new_curr = malloc(sizeof(type##_ploods_node));                                                          \
      new_curr->value = value;                                                                                                    \
      new_curr->prev = d->curr;                                                                                                   \
      d->curr->next = new_curr;                                                                                                   \
      d->curr = new_curr;                                                                                                         \
                                                                                                                                  \
      d->size++;                                                                                                                  \
                                                                                                                                  \
      return;                                                                                                                     \
    }                                                                                                                             \
                                                                                                                                  \
    type##_ploods_node* trav;                                                                                                     \
    if (pos < d->size / 2) {                                                                                                      \
      trav = d->root;                                                                                                             \
      uint32_t i;                                                                                                                 \
      for (i = 0; i < pos - 1; i++)                                                                                               \
        trav = trav->next;                                                                                                        \
    }                                                                                                                             \
    if (pos >= d->size / 2) {                                                                                                     \
      trav = d->curr;                                                                                                             \
      uint32_t i;                                                                                                                 \
      for (i = 0; i < d->size - pos; i++)                                                                                         \
        trav = trav->prev;                                                                                                        \
    }                                                                                                                             \
    type##_ploods_node* new_node = malloc(sizeof(type##_ploods_node));                                                            \
    new_node->value = value;                                                                                                      \
    new_node->prev = trav;                                                                                                        \
    new_node->next = trav->next;                                                                                                  \
    trav->next = new_node;                                                                                                        \
    new_node->next->prev = new_node;                                                                                              \
                                                                                                                                  \
    d->size++;                                                                                                                    \
  }                                                                                                                               \
                                                                                                                                  \
  void type##_erase(type##_ploods* d, const uint32_t pos) {                                                                       \
    if (d == NULL)                                                                                                                \
      return;                                                                                                                     \
                                                                                                                                  \
    if (pos + 1 > d->size)                                                                                                        \
      return;                                                                                                                     \
    if (d->size == 0)                                                                                                             \
      return;                                                                                                                     \
    if (pos == 0) {                                                                                                               \
      type##_ploods_node* to_delete = d->root;                                                                                    \
      d->root = d->root->next;                                                                                                    \
      free(to_delete);                                                                                                            \
      d->curr->next = NULL;                                                                                                       \
      d->root->prev = NULL;                                                                                                       \
                                                                                                                                  \
      d->size--;                                                                                                                  \
                                                                                                                                  \
      return;                                                                                                                     \
    }                                                                                                                             \
    if (pos == d->size - 1) {                                                                                                     \
      type##_ploods_node* to_delete = d->curr;                                                                                    \
      d->curr = d->curr->prev;                                                                                                    \
      free(to_delete);                                                                                                            \
      d->root->prev = NULL;                                                                                                       \
      d->curr->next = NULL;                                                                                                       \
                                                                                                                                  \
      d->size--;                                                                                                                  \
                                                                                                                                  \
      return;                                                                                                                     \
    }                                                                                                                             \
                                                                                                                                  \
    type##_ploods_node* trav;                                                                                                     \
    if (pos < d->size / 2) {                                                                                                      \
      trav = d->root;                                                                                                             \
      uint32_t i;                                                                                                                 \
      for (i = 0; i < pos; i++)                                                                                                   \
        trav = trav->next;                                                                                                        \
    }                                                                                                                             \
    if (pos >= d->size / 2) {                                                                                                     \
      trav = d->curr;                                                                                                             \
      uint32_t i;                                                                                                                 \
      for (i = 0; i < d->size - pos - 1; i++)                                                                                     \
        trav = trav->prev;                                                                                                        \
    }                                                                                                                             \
    trav->prev->next = trav->next;                                                                                                \
    trav->next->prev = trav->prev;                                                                                                \
    free(trav);                                                                                                                   \
    trav = NULL;                                                                                                                  \
                                                                                                                                  \
    d->size--;                                                                                                                    \
  }                                                                                                                               \
                                                                                                                                  \
  void type##_reverse(type##_ploods* d) {                                                                                         \
    if (d == NULL)                                                                                                                \
      return;                                                                                                                     \
                                                                                                                                  \
    type##_ploods_node* trav = d->root;                                                                                           \
    type##_ploods_node* temp;                                                                                                     \
    type##_ploods_node* swapper;                                                                                                  \
    uint32_t i;                                                                                                                   \
    for (i = 0; i < d->size; i++) {                                                                                               \
      temp = trav;                                                                                                                \
      trav = trav->next;                                                                                                          \
      swapper = temp->next;                                                                                                       \
      temp->next = temp->prev;                                                                                                    \
      temp->prev = swapper;                                                                                                       \
    }                                                                                                                             \
    temp = d->root;                                                                                                               \
    d->root = d->curr;                                                                                                            \
    d->curr = temp;                                                                                                               \
    temp = NULL;                                                                                                                  \
    swapper = NULL;                                                                                                               \
    trav = NULL;                                                                                                                  \
  }                                                                                                                               \
                                                                                                                                  \
  int64_t type##_find(type##_ploods* d, const uint32_t pos, const type value) {                                                   \
    if (d == NULL)                                                                                                                \
      return -1;                                                                                                                  \
                                                                                                                                  \
    type##_ploods_node* trav = d->root;                                                                                           \
    uint32_t i;                                                                                                                   \
    for (i = 0; i < pos; i++)                                                                                                     \
      trav = trav->next;                                                                                                          \
    for (i = pos; i < d->size; i++) {                                                                                             \
      if (trav->value == value)                                                                                                   \
        return i;                                                                                                                 \
      trav = trav->next;                                                                                                          \
    }                                                                                                                             \
                                                                                                                                  \
    return -1;                                                                                                                    \
  }                                                                                                                               \
                                                                                                                                  \
  int64_t type##_size(type##_ploods* d) {                                                                                         \
    if (d == NULL)                                                                                                                \
      return -1;                                                                                                                  \
                                                                                                                                  \
    return d->size;                                                                                                               \
  }                                                                                                                               \
                                                                                                                                  \
  int8_t type##_empty(type##_ploods* d) {                                                                                         \
    if (d == NULL)                                                                                                                \
      return -1;                                                                                                                  \
                                                                                                                                  \
    return d->size == 0;                                                                                                          \
  }

#endif


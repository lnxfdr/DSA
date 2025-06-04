#ifndef MAXHEAP_H
#define MAXHEAP_H
#include <stdlib.h>
#include <stdint.h>

#define CREATE_MAXHEAP(type)                                                                              \
                                                                                                          \
  typedef struct type##_maxHeap {                                                                         \
                                                                                                          \
    void     (*_initialize)(struct type##_maxHeap* h);                                                    \
    void     (*_dispose)(struct type##_maxHeap* h);                                                       \
    void     (*_move_values)(struct type##_maxHeap* h, const uint32_t capacity);                          \
    void     (*_change_sizing_factor)(struct type##_maxHeap* h, const float new_factor);                  \
    void     (*_reserve)(struct type##_maxHeap* h, const uint32_t capacity);                              \
    void     (*_push)(struct type##_maxHeap* h, const type value);                                        \
    void     (*_pop)(struct type##_maxHeap* h);                                                           \
    type     (*_top)(struct type##_maxHeap* h);                                                           \
    int64_t  (*_size)(struct type##_maxHeap* h);                                                          \
    int64_t  (*_capacity)(struct type##_maxHeap* h);                                                      \
    int8_t   (*_empty)(struct type##_maxHeap* h);                                                         \
                                                                                                          \
    float    sizing_factor;                                                                               \
                                                                                                          \
    type*    data;                                                                                        \
    uint32_t size;                                                                                        \
    uint32_t capacity;                                                                                    \
  } type##_maxHeap;                                                                                       \
                                                                                                          \
  void type##_initialize(type##_maxHeap* h) {                                                             \
    if (h == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    h->sizing_factor = 1.5;                                                                               \
                                                                                                          \
    h->size = 0;                                                                                          \
    h->capacity = 2;                                                                                      \
                                                                                                          \
    h->data = malloc(sizeof(type) * h->capacity);                                                         \
  }                                                                                                       \
                                                                                                          \
  void type##_dispose(type##_maxHeap* h) {                                                                \
    if (h == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    free(h->data);                                                                                        \
    h->data = NULL;                                                                                       \
  }                                                                                                       \
                                                                                                          \
  void type##_move_values(type##_maxHeap* h, const uint32_t capacity) {                                   \
    if (h == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    type* temp = malloc(sizeof(type) * capacity);                                                         \
    uint32_t i;                                                                                           \
    for (i = 0; i < (h->size < capacity ? h->size : capacity); i++)                                       \
      temp[i] = h->data[i];                                                                               \
    free(h->data);                                                                                        \
    h->data = temp;                                                                                       \
    temp = NULL;                                                                                          \
  }                                                                                                       \
                                                                                                          \
  void type##_change_sizing_factor(type##_maxHeap* h, const float new_factor) {                           \
    if (h == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    h->sizing_factor = new_factor;                                                                        \
  }                                                                                                       \
                                                                                                          \
  void type##_reserve(type##_maxHeap* h, const uint32_t capacity) {                                       \
    if (h == NULL)                                                                                        \
      return;                                                                                             \                                                                                                                                                         \
    type##_move_values(h, capacity);                                                                      \
    h->capacity = capacity;                                                                               \
  }                                                                                                       \
                                                                                                          \
  void type##_upsize(type##_maxHeap* h) {                                                                 \
    if (h == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    type##_move_values(h, (uint32_t)h->capacity * h->sizing_factor);                                      \
    h->capacity = (uint32_t)h->capacity * h->sizing_factor;                                               \
  }                                                                                                       \
                                                                                                          \
  void type##_downsize(type##_maxHeap* h) {                                                               \
    if (h == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    type##_move_values(h, (uint32_t)h->capacity / h->sizing_factor);                                      \
    h->capacity = (uint32_t)h->capacity / h->sizing_factor;                                               \
  }                                                                                                       \
                                                                                                          \
  void type##_swap(type##_maxHeap* h, const uint32_t i, const uint32_t j) {                               \
    if (h == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    type temp = h->data[i];                                                                               \
    h->data[i] = h->data[j];                                                                              \
    h->data[j] = temp;                                                                                    \
  }                                                                                                       \
                                                                                                          \
  void type##_upsift(type##_maxHeap* h) {                                                                 \
    if (h == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    uint32_t i = h->size - 1;                                                                             \
    while (i > 0 && h->data[i] > h->data[(i - 1) / 2]) {                                                  \
      type##_swap(h, i, (i - 1) / 2);                                                                     \
      i = (i - 1) / 2;                                                                                    \
    }                                                                                                     \
  }                                                                                                       \
                                                                                                          \
  void type##_downsift(type##_maxHeap* h) {                                                               \
    if (h == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    uint32_t i = 0;                                                                                       \
    uint8_t ok = 0;                                                                                       \
    while (i * 2 + 2 < h->size) {                                                                         \
      ok = 0;                                                                                             \
      if (h->data[i * 2 + 1] > h->data[i] && h->data[i * 2 + 2] > h->data[i]) {                           \
        if (h->data[i * 2 + 1] > h->data[i * 2 + 2]) {                                                    \
          type##_swap(h, i, i * 2 + 1);                                                                   \
          i = i * 2 + 1;                                                                                  \
          ok = 1;                                                                                         \
        }                                                                                                 \
        else {                                                                                            \
          type##_swap(h, i, i * 2 + 2);                                                                   \
          i = i * 2 + 2;                                                                                  \
          ok = 1;                                                                                         \
        }                                                                                                 \
      }                                                                                                   \
      else if (h->data[i * 2 + 2] > h->data[i] && h->data[i * 2 + 1] <= h->data[i]) {                     \
        type##_swap(h, i, i * 2 + 2);                                                                     \
        i = i * 2 + 2;                                                                                    \
        ok = 1;                                                                                           \
      }                                                                                                   \
      else if (h->data[i * 2 + 1] > h->data[i] && h->data[i * 2 + 2] <= h->data[i]) {                     \
        type##_swap(h, i, i * 2 + 1);                                                                     \
        i = i * 2 + 1;                                                                                    \
        ok = 1;                                                                                           \
      }                                                                                                   \
      if (ok == 0)                                                                                        \
        break;                                                                                            \
    }                                                                                                     \
    if (i * 2 + 1 == h->size - 1 && h->data[i * 2 + 1] > h->data[i])                                      \
      type##_swap(h, i, i * 2 + 1);                                                                       \
  }                                                                                                       \
                                                                                                          \
  void type##_push(type##_maxHeap* h, const type value) {                                                 \
    if (h == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    if (h->size == h->capacity)                                                                           \
      type##_upsize(h);                                                                                   \
                                                                                                          \
    h->data[h->size++] = value;                                                                           \
    type##_upsift(h);                                                                                     \
  }                                                                                                       \
                                                                                                          \
  void type##_pop(type##_maxHeap* h) {                                                                    \
    if (h == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    if (h->size == 0)                                                                                     \
      return;                                                                                             \
    if ((uint32_t)h->size * h->sizing_factor < (uint32_t)h->capacity / h->sizing_factor)                  \
      type##_downsize(h);                                                                                 \
                                                                                                          \
    h->size--;                                                                                            \
                                                                                                          \
    h->data[0] = h->data[h->size];                                                                        \
    type##_downsift(h);                                                                                   \
  }                                                                                                       \
                                                                                                          \
  type type##_top(type##_maxHeap* h) {                                                                    \
    if (h == NULL) {                                                                                      \
      type zero = {0};                                                                                    \
      return zero;                                                                                        \
    }                                                                                                     \
                                                                                                          \
    return h->data[0];                                                                                    \
  }                                                                                                       \
                                                                                                          \
  int64_t type##_size(type##_maxHeap* h) {                                                                \
    if (h == NULL)                                                                                        \
      return -1;                                                                                          \
                                                                                                          \
    return h->size;                                                                                       \
  }                                                                                                       \
                                                                                                          \
  int64_t type##_capacity(type##_maxHeap* h) {                                                            \
    if (h == NULL)                                                                                        \
      return -1;                                                                                          \
                                                                                                          \
    return h->capacity;                                                                                   \
  }                                                                                                       \
                                                                                                          \
  int8_t type##_empty(type##_maxHeap* h) {                                                                \
    if (h == NULL)                                                                                        \
      return -1;                                                                                          \
                                                                                                          \
    return h->size == 0;                                                                                  \
  }

#define BUILD_MAXHEAP(h, type)                                                                            \
  h._initialize = type##_initialize;                                                                      \
  h._dispose = type##_dispose;                                                                            \
  h._move_values = type##_move_values;                                                                    \
  h._reserve = type##_reserve;                                                                            \
  h._push = type##_push;                                                                                  \
  h._pop = type##_pop;                                                                                    \
  h._top = type##_top;                                                                                    \
  h._size = type##_size;                                                                                  \
  h._capacity = type##_capacity;                                                                          \
  h._empty = type##_empty;

#endif


/* Sequential Memory Organized and Optimized Data Structure */
#ifndef SMOODS_H
#define SMOODS_H
#include <stdlib.h>
#include <stdint.h>

#define CREATE_SMOODS(type)                                                                               \
                                                                                                          \
  typedef struct type##_smoods {                                                                          \
                                                                                                          \
    void     (*_initialize)(struct type##_smoods* d);                                                     \
    void     (*_dispose)(struct type##_smoods* s);                                                        \
    void     (*_change_sizing_factor)(struct type##_smoods* s, const float new_factor);                   \
    int64_t  (*_front_index)(struct type##_smoods* s, const uint32_t pos, const uint32_t capacity);       \
    int64_t  (*_back_index)(struct type##_smoods* s, const uint32_t pos, const uint32_t capacity);        \
    int64_t  (*_next_index)(struct type##_smoods* s, const uint32_t pos, const uint32_t capacity);        \
    int64_t  (*_prev_index)(struct type##_smoods* s, const uint32_t pos, const uint32_t capacity);        \
    void     (*_reserve)(struct type##_smoods* s, const uint32_t size);                                   \
    void     (*_push_front)(struct type##_smoods* s, const type value);                                   \
    void     (*_push_back)(struct type##_smoods* s, const type value);                                    \
    void     (*_insert)(struct type##_smoods* s, const uint32_t pos, const type value);                   \
    void     (*_pop_front)(struct type##_smoods* s);                                                      \
    void     (*_pop_back)(struct type##_smoods* s);                                                       \
    void     (*_erase)(struct type##_smoods* s, const uint32_t pos);                                      \
    void     (*_reverse)(struct type##_smoods* s);                                                        \
    int64_t  (*_find)(struct type##_smoods* s, const uint32_t pos, const type value);                     \
    type     (*_at)(struct type##_smoods* s, const uint32_t pos);                                         \
    void     (*_change_at)(struct type##_smoods* s, const uint32_t pos, const type value);                \
    int64_t  (*_size)(struct type##_smoods* s);                                                           \
    int64_t  (*_capacity)(struct type##_smoods* s);                                                       \
    int8_t   (*_empty)(struct type##_smoods* s);                                                          \
    void     (*_clear)(struct type##_smoods* s);                                                          \
                                                                                                          \
    float    sizing_factor;                                                                               \
                                                                                                          \
    type*    data;                                                                                        \
    uint32_t front_index;                                                                                 \
    uint32_t back_index;                                                                                  \
    uint32_t size;                                                                                        \
    uint32_t capacity;                                                                                    \
  } type##_smoods;                                                                                        \
                                                                                                          \
  void type##_initialize(type##_smoods* s) {                                                              \
    if (s == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    s->sizing_factor = 1.5;                                                                               \
                                                                                                          \
    s->front_index = 0;                                                                                   \
    s->back_index = 1;                                                                                    \
                                                                                                          \
    s->size = 0;                                                                                          \
    s->capacity = 2;                                                                                      \
                                                                                                          \
    s->data = malloc(sizeof(type) * s->capacity);                                                         \
  }                                                                                                       \
                                                                                                          \
  void type##_dispose(type##_smoods* s) {                                                                 \
    if (s == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    free(s->data);                                                                                        \
    s->data = NULL;                                                                                       \
  }                                                                                                       \
                                                                                                          \
  void type##_change_sizing_factor(type##_smoods* s, const float new_factor) {                            \
    if (s == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    s->sizing_factor = new_factor;                                                                        \
  }                                                                                                       \
                                                                                                          \
  int64_t type##_front_index(type##_smoods* s, const uint32_t i, const uint32_t capacity) {               \
    if (s == NULL)                                                                                        \
      return -1;                                                                                          \
                                                                                                          \
    return (s->front_index + 1 + i) % capacity;                                                           \
  }                                                                                                       \
                                                                                                          \
  int64_t type##_back_index(type##_smoods* s, const uint32_t i, const uint32_t capacity) {                \
    if (s == NULL)                                                                                        \
      return -1;                                                                                          \
                                                                                                          \
    return (s->back_index - 1 - i + capacity) % capacity;                                                 \
  }                                                                                                       \
                                                                                                          \
  int64_t type##_next_index(type##_smoods* s, const uint32_t pos, const uint32_t capacity) {              \
    if (s == NULL)                                                                                        \
      return -1;                                                                                          \
                                                                                                          \
    return (pos + 1) % capacity;                                                                          \
  }                                                                                                       \
                                                                                                          \
  int64_t type##_prev_index(type##_smoods* s, const uint32_t pos, const uint32_t capacity) {              \
    if (s == NULL)                                                                                        \
      return -1;                                                                                          \
                                                                                                          \
    return (pos - 1 + capacity) % capacity;                                                               \
  }                                                                                                       \
                                                                                                          \
  void type##_move_values(type##_smoods* s, const uint32_t size, const uint32_t capacity) {               \
    if (s == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    type* temp = malloc(sizeof(type) * capacity);                                                         \
    if (temp == NULL)                                                                                     \
      return;                                                                                             \
                                                                                                          \
    uint32_t i;                                                                                           \
    for (i = 0; i < size + 1; i++)                                                                        \
      temp[i] = s->data[type##_front_index(s, i, size + 1)];                                              \
    free(s->data);                                                                                        \
    s->data = temp;                                                                                       \
    temp = NULL;                                                                                          \
  }                                                                                                       \
                                                                                                          \
  void type##_reserve(type##_smoods* s, const uint32_t size) {                                            \
    if (s == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    type##_move_values(s, s->size, size);                                                                 \
                                                                                                          \
    s->front_index = size - 1;                                                                            \
    s->back_index = s->size;                                                                              \
                                                                                                          \
    s->capacity = size;                                                                                   \
  }                                                                                                       \
                                                                                                          \
  void type##_upsize(type##_smoods* s) {                                                                  \
    if (s == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    s->capacity = (uint32_t)s->capacity * s->sizing_factor;                                               \
    type##_move_values(s, s->size, s->capacity);                                                          \
                                                                                                          \
    s->front_index = s->capacity - 1;                                                                     \
    s->back_index = s->size;                                                                              \
  }                                                                                                       \
                                                                                                          \
  void type##_downsize(type##_smoods* s) {                                                                \
    if (s == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    uint32_t new_capacity = (uint32_t)s->capacity / s->sizing_factor;                                     \
    type##_move_values(s, s->size, new_capacity);                                                         \
                                                                                                          \
    s->front_index = new_capacity - 1;                                                                    \
    s->back_index = s->size;                                                                              \
                                                                                                          \
    s->capacity = new_capacity;                                                                           \
  }                                                                                                       \
                                                                                                          \
  void type##_push_front(type##_smoods* s, const type value) {                                            \
    if (s == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    if (s->front_index == s->back_index)                                                                  \
      type##_upsize(s);                                                                                   \
                                                                                                          \
    s->data[s->front_index] = value;                                                                      \
                                                                                                          \
    s->front_index = type##_prev_index(s, s->front_index, s->capacity);                                   \
                                                                                                          \
    s->size++;                                                                                            \
  }                                                                                                       \
                                                                                                          \
  void type##_push_back(type##_smoods* s, const type value) {                                             \
    if (s == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    if (s->front_index == s->back_index)                                                                  \
      type##_upsize(s);                                                                                   \
                                                                                                          \
    s->data[s->back_index] = value;                                                                       \
                                                                                                          \
    s->back_index = type##_next_index(s, s->back_index, s->capacity);                                     \
                                                                                                          \
    s->size++;                                                                                            \
  }                                                                                                       \
                                                                                                          \
  void type##_insert(type##_smoods* s, const uint32_t pos, const type value) {                            \
    if (s == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    if (pos > s->size)                                                                                    \
      return;                                                                                             \
    if (s->size == 0) {                                                                                   \
      type##_push_back(s, value);                                                                         \
      return;                                                                                             \
    }                                                                                                     \
    if (pos == 0) {                                                                                       \
      type##_push_front(s, value);                                                                        \
      return;                                                                                             \
    }                                                                                                     \
    if (pos == s->size) {                                                                                 \
      type##_push_back(s, value);                                                                         \
      return;                                                                                             \
    }                                                                                                     \
    if (s->size == s->capacity)                                                                           \
      type##_upsize(s);                                                                                   \
                                                                                                          \
    int32_t i;                                                                                            \
    i = type##_back_index(s, 0, s->capacity);                                                             \
    while (i != type##_front_index(s, pos, s->capacity)) {                                                \
      s->data[(i + 1) % s->capacity] = s->data[i];                                                        \
      i = (i - 1 + s->capacity) % s->capacity;                                                            \
    }                                                                                                     \
    s->data[(i + 1) % s->capacity] = s->data[i];                                                          \
    s->data[type##_front_index(s, pos, s->capacity)] = value;                                             \
                                                                                                          \
    s->back_index = type##_next_index(s, s->back_index, s->capacity);                                     \
                                                                                                          \
    s->size++;                                                                                            \
  }                                                                                                       \
                                                                                                          \
  void type##_pop_front(type##_smoods* s) {                                                               \
    if (s == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    if (s->size == 0)                                                                                     \
      return;                                                                                             \
    if ((uint32_t)s->size * s->sizing_factor < (uint32_t)s->capacity / s->sizing_factor)                  \
      type##_downsize(s);                                                                                 \
                                                                                                          \
    s->front_index = type##_next_index(s, s->front_index, s->capacity);                                   \
                                                                                                          \
    s->size--;                                                                                            \
  }                                                                                                       \
                                                                                                          \
  void type##_pop_back(type##_smoods* s) {                                                                \
    if (s == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    if (s->size == 0)                                                                                     \
      return;                                                                                             \
    if ((uint32_t)s->size * s->sizing_factor < (uint32_t)s->capacity / s->sizing_factor)                  \
      type##_downsize(s);                                                                                 \
                                                                                                          \
    s->back_index = type##_prev_index(s, s->back_index, s->capacity);                                     \
                                                                                                          \
    s->size--;                                                                                            \
  }                                                                                                       \
                                                                                                          \
  void type##_erase(type##_smoods* s, const uint32_t pos) {                                               \
    if (s == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    if (pos > s->size)                                                                                    \
      return;                                                                                             \
    if (s->size == 0)                                                                                     \
      return;                                                                                             \
    if (pos == 0) {                                                                                       \
      type##_pop_front(s);                                                                                \
      return;                                                                                             \
    }                                                                                                     \
    if (pos == s->size) {                                                                                 \
      type##_pop_back(s);                                                                                 \
      return;                                                                                             \
    }                                                                                                     \
    if ((uint32_t)s->size * s->sizing_factor < (uint32_t)s->capacity / s->sizing_factor)                  \
      type##_downsize(s);                                                                                 \
                                                                                                          \
    int32_t i;                                                                                            \
    i = type##_front_index(s, pos, s->capacity);                                                          \
    while (i != type##_back_index(s, 0, s->capacity)) {                                                   \
      s->data[i] = s->data[(i + 1) % s->capacity];                                                        \
      i = (i + 1) % s->capacity;                                                                          \
    }                                                                                                     \
    s->data[i] = s->data[(i + 1) % s->capacity];                                                          \
                                                                                                          \
    s->back_index = type##_back_index(s, 0, s->capacity);                                                 \
                                                                                                          \
    s->size--;                                                                                            \
  }                                                                                                       \
                                                                                                          \
  void type##_reverse(type##_smoods* s) {                                                                 \
    if (s == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    uint32_t i;                                                                                           \
    for (i = 0; i < s->size / 2; i++) {                                                                   \
      type temp;                                                                                          \
      temp = s->data[type##_front_index(s, i, s->capacity)];                                              \
      s->data[type##_front_index(s, i, s->capacity)] = s->data[type##_back_index(s, i, s->capacity)];     \
      s->data[type##_back_index(s, i, s->capacity)] = temp;                                               \
    }                                                                                                     \
  }                                                                                                       \
                                                                                                          \
  int64_t type##_find(type##_smoods* s, const uint32_t pos, const type value) {                           \
    if (s == NULL)                                                                                        \
      return -1;                                                                                          \
                                                                                                          \
    uint32_t i;                                                                                           \
    for (i = pos; i < s->size; i++) {                                                                     \
      if (s->data[type##_front_index(s, i, s->capacity)] == value)                                        \
        return i;                                                                                         \
    }                                                                                                     \
    return -1;                                                                                            \
  }                                                                                                       \
                                                                                                          \
  type type##_at(type##_smoods* s, const uint32_t pos) {                                                  \
    if (s == NULL) {                                                                                      \
      type zero = {0};                                                                                    \
      return zero;                                                                                        \
    }                                                                                                     \
                                                                                                          \
    if (pos < s->size)                                                                                    \
      return s->data[type##_front_index(s, pos, s->capacity)];                                            \
                                                                                                          \
    type zero = {0};                                                                                      \
    return zero;                                                                                          \
  }                                                                                                       \
                                                                                                          \
  void type##_change_at(type##_smoods* s, const uint32_t pos, const type value) {                         \
    if (s == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    if (pos < s->size)                                                                                    \
      s->data[type##_front_index(s, pos, s->capacity)] = value;                                           \
  }                                                                                                       \
                                                                                                          \
  int64_t type##_size(type##_smoods* s) {                                                                 \
    if (s == NULL)                                                                                        \
      return -1;                                                                                          \
                                                                                                          \
    return s->size;                                                                                       \
  }                                                                                                       \
                                                                                                          \
  int64_t type##_capacity(type##_smoods* s) {                                                             \
    if (s == NULL)                                                                                        \
      return -1;                                                                                          \
                                                                                                          \
    return s->capacity;                                                                                   \
  }                                                                                                       \
                                                                                                          \
  int8_t type##_empty(type##_smoods* s) {                                                                 \
    if (s == NULL)                                                                                        \
      return -1;                                                                                          \
                                                                                                          \
    return s->size == 0;                                                                                  \
  }                                                                                                       \
                                                                                                          \
  void type##_clear(type##_smoods* s) {                                                                   \
    if (s == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    s->front_index = 0;                                                                                   \
    s->back_index = 1;                                                                                    \
                                                                                                          \
    s->size = 0;                                                                                          \
}

#define BUILD_SMOODS(s, type)                                                                             \
  s._initialize = type##_initialize;                                                                      \
  s._dispose = type##_dispose;                                                                            \
  s._change_sizing_factor = type##_change_sizing_factor;                                                  \
  s._front_index = type##_front_index;                                                                    \
  s._back_index = type##_back_index;                                                                      \
  s._next_index = type##_next_index;                                                                      \
  s._prev_index = type##_prev_index;                                                                      \
  s._reserve = type##_reserve;                                                                            \
  s._push_front = type##_push_front;                                                                      \
  s._push_back = type##_push_back;                                                                        \
  s._insert = type##_insert;                                                                              \
  s._pop_front = type##_pop_front;                                                                        \
  s._pop_back = type##_pop_back;                                                                          \
  s._erase = type##_erase;                                                                                \
  s._reverse = type##_reverse;                                                                            \
  s._find = type##_find;                                                                                  \
  s._at = type##_at;                                                                                      \
  s._change_at = type##_change_at;                                                                        \
  s._size = type##_size;                                                                                  \
  s._capacity = type##_capacity;                                                                          \
  s._empty = type##_empty;                                                                                \
  s._clear = type##_clear;

#endif


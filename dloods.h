#ifndef DLOODS_H
#define DLOODS_H

#define CREATE_DLOODS(type)\
\
  typedef struct type##_dloods_node {\
\
    type value;\
    struct type##_dloods_node* next;\
    struct type##_dloods_node* prev;\
  } type##_dloods_node;\
\
  typedef struct type##_dloods {\
\
    void (*_initialize)(struct type##_dloods* d);\
    void (*_dispose)(struct type##_dloods* d);\
    void (*_make_circular)(struct type##_dloods* d);\
    type##_dloods_node* (*_get_node)(struct type##_dloods* d, const uint32_t pos);\
    type##_dloods_node* (*_next_node)(struct type##_dloods* d, type##_dloods_node* n);\
    type##_dloods_node* (*_prev_node)(struct type##_dloods* d, type##_dloods_node* n);\
    type (*_node_value)(struct type##_dloods* d, type##_dloods_node* n);\
    void (*_change_node_value)(struct type##_dloods* d, type##_dloods_node* n, const type value);\
    void (*_insert)(struct type##_dloods* d, const uint32_t pos, const type value);\
    void (*_erase)(struct type##_dloods* d, const uint32_t pos);\
    void (*_reverse)(struct type##_dloods* d);\
    int64_t (*_find)(struct type##_dloods* d, const uint32_t pos, const type value);\
    int64_t (*_size)(struct type##_dloods* d);\
    int8_t (*_empty)(struct type##_dloods* d);\


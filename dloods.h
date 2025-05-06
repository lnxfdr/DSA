#ifndef DLOODS_H
#define DLOODS_H

#define CREATE_DLOODS(type)\
\
  typedef struct type##_dloods_node {\
\
    type                       value;\
    struct type##_dloods_node* next;\
    struct type##_dloods_node* prev;\
  } type##_dloods_node;\
\
  typedef struct type##_dloods {\
\
    void                (*_initialize)(struct type##_dloods* d);\
    void                (*_dispose)(struct type##_dloods* d);\
    void                (*_make_circular)(struct type##_dloods* d);\
    type##_dloods_node* (*_get_node)(struct type##_dloods* d, const uint32_t pos);\
    type##_dloods_node* (*_next_node)(struct type##_dloods* d, type##_dloods_node* n);\
    type##_dloods_node* (*_prev_node)(struct type##_dloods* d, type##_dloods_node* n);\
    type                (*_node_value)(struct type##_dloods* d, type##_dloods_node* n);\
    void                (*_change_node_value)(struct type##_dloods* d, type##_dloods_node* n, const type value);\
    void                (*_insert)(struct type##_dloods* d, const uint32_t pos, const type value);\
    void                (*_erase)(struct type##_dloods* d, const uint32_t pos);\
    void                (*_reverse)(struct type##_dloods* d);\
    int64_t             (*_find)(struct type##_dloods* d, const uint32_t pos, const type value);\
    int64_t             (*_size)(struct type##_dloods* d);\
    int8_t              (*_empty)(struct type##_dloods* d);\
\
    type##_dloods_node* root;\
    type##_dloods_node* curr;\
    uint32_t            size;\
  } type##_dloods;\
\
  void type##_initialize(type##_dloods* d) {\
    if (d == NULL)\
      return;\
\
    d->size = 0;\
\
    d->root = (type##_dloods_node*)malloc(sizeof(type##_dloods_node));\
    d->curr = d->root;\
  }\
\
  void type##_dispose(type##_dloods* d) {\
    if (d == NULL)\
      return;\
\
    type##_dloods_node* to_delete;\
    while(root != NULL) {\
      to_delete = d->root;\
      d->root = d->root->next;\
      free(to_delete);\
    }\
    d->root = NULL;\
    d->curr = NULL;\
  }\
\
  void type##_make_circular(type##_dloods* d) {\
    if (d == NULL)\
      return;\
\
    d->root->prev = d->curr;\
    d->curr->next = d->root;\
  }\
\
  type##_dloods_node* type##_get_node(type##_dloods* d, const uint32_t pos) {\
    if (d == NULL)\
      return NULL;\
\
    type##_dloods_node* trav = d->root;\
    uint32_t i;\
    for (i = 0; i < pos; i++)\
      trav = trav->next;\
    return trav;\
  }\
\
  type##_dloods_node* type##_next_node(type##_dloods* d, type##_dloods_node* n) {\
    if (d == NULL)\
      return NULL;\
    if (n == NULL)\
      return NULL;\
\
    return n->next;\
  }\
\
  type##_dloods_node* type##_prev_node(type##_dloods* d, type##_dloods_node* n) {\
    if (d == NULL)\
      return NULL;\
    if (n == NULL)\
      return NULL;\
\
    return n->prev;\
  }\
\
  type type##_node_value(type##_dloods* d, type##_dloods_node* n) {\
    if (d == NULL) {\
      type zero = {0};\
      return zero;\
    }\
    if (n == NULL) {\
      type zero = {0};\
      return zero;\
    }\
\
    return n->value;\
  }\
\
  void type##_change_node_value(type##_dloods* d, type##_dloods_node* n, const type value) {\
    if (d == NULL)\
      return;\
    if (n == NULL)\
      return;\
\
    n->value = value;\
  }\
\
  void type##_insert(type##_dloods* d, const uint32_t pos, const type value) {\
    
#define BUILD_DLOODS(d, type)\
  d._initialize = type##_initialize;\
  d._dispose = type##_dispose;\
  d._make_circular = type##_make_circular;\
  d._get_node = type##_get_node;\
  d._next_node = type##_next_node;\
  d._prev_node = type##_prev_node;\
  d._node_value = type##_node_value;\
  d._change_node_value = type##_change_node_value;\
  d._insert = type##_insert;\
  d._erase = type##_erase;\
  d._reverse = type##_reverse;\
  d._find = type##_find;\
  d._size = type##_size;\
  d._empty = type##_empty;

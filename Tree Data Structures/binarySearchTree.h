#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <stdlib.h>
#include <stdint.h>

#define CREATE_BST(type)\
\
  typedef struct type##_binarySearchTreeNode {\
\
    type            value;\
    struct type##_binarySearchTreeNode* parent;\
    struct type##_binarySearchTreeNode* left;\
    struct type##_binarySearchTreeNode* right;\
  } type##_bstNode;\
\
  typedef struct type##_binarySearchTree {\
\
    void            (*_initialize)(struct type##_binarySearchTree* b);\
    void            (*_dispose)(struct type##_binarySearchTree* b);\
    type##_bstNode* (*_get_first_node)(struct type##_binarySearchTree* b);\
    type##_bstNode* (*_get_last_node)(struct type##_binarySearchTree* b);\
    type##_bstNode* (*_get_node)(struct type##_binarySearchTree* b, type value);\
    type##_bstNode* (*_next_node)(struct type##_binarySearchTree* b, type##_bstNode* n);\
    type##_bstNode* (*_prev_node)(struct type##_binarySearchTree* b, type##_bstNode* n);\
    type            (*_node_value)(struct type##_binarySearchTree* b, type##_bstNode* n);\
    void            (*_insert)(struct type##_binarySearchTree* b, type value);\
    void            (*_erase)(struct type##_binarySearchTree* b, type value);\
    int64_t         (*_size)(struct type##_binarySearchTree* b);\
    int8_t          (*_empty)(struct type##_binarySearchTree* b);\
\
    type##_bstNode* root;\
    uint32_t        size;\
  } type##_bst;\
\
  void type##_inorder_delete(type##_bst* b, type##_bstNode* r) {\
    if (b == NULL || r == NULL)\
      return;\
\
    type##_inorder_delete(b, r->left);\
    type##_inorder_delete(b, r->right);\
    if (r != NULL)\
      free(r);\
    r = NULL;\
  }\
\
  void type##_initialize(type##_bst* b) {\
    if (b == NULL)\
      return;\
\
    b->size = 0;\
\
    b->root = (type##_bstNode*)malloc(sizeof(type##_bstNode));\
  }\
\
  void type##_dispose(type##_bst* b) {\
    if (b == NULL)\
      return;\
\
    type##_inorder_delete(b, b->root);\
  }\
\
  type##_bstNode* type##_get_first_node(type##_bst* b) {\
    if (b == NULL)\
      return NULL;\
\
    type##_bstNode* trav = b->root;\
    while (trav->left != NULL)\
      trav = trav->left;\
    return trav;\
  }\
\
  type##_bstNode* type##_get_last_node(type##_bst* b) {\
    if (b == NULL)\
      return NULL;\
\
    type##_bstNode* trav = b->root;\
    while (trav->right != NULL)\
      trav = trav->right;\
    return trav;\
  }\
\
  type##_bstNode* type##_get_node(type##_bst* b, type value) {\
    if (b == NULL)\
      return NULL;\
\
    type##_bstNode* trav = b->root;\
    while (trav != NULL) {\
      if (value == trav->value)\
        return trav;\
      else if (value < trav->value && trav->left != NULL)\
        trav = trav->left;\
      else if (value > trav->value && trav->right != NULL)\
        trav = trav->right;\
      else\
        return NULL;\
    }\
    return NULL;\
  }\
\
  type##_bstNode* type##_next_node(type##_bst* b, type##_bstNode* n) {\
    if (b == NULL || n == NULL)\
      return NULL;\
\
    type##_bstNode* trav = n;\
    if (trav->right == NULL) {\
      while (trav == trav->parent->right)\
        trav = trav->parent;\
      return trav->parent;\
    }\
    trav = trav->right;\
    while (trav->left != NULL)\
      trav = trav->left;\
    return trav;\
  }\
\
  type##_bstNode* type##_prev_node(type##_bst* b, type##_bstNode* n) {\
    if (b == NULL || n == NULL)\
      return NULL;\
\
    type##_bstNode* trav = n;\
    if (trav->left == NULL) {\
      while (trav == trav->parent->left)\
        trav = trav->parent;\
      return trav->parent;\
    }\
    trav = trav->left;\
    while (trav->right != NULL)\
      trav = trav->right;\
    return trav;\
  }\
\
  type type##_node_value(type##_bst* b, type##_bstNode* n) {\
    if (b == NULL || n == NULL) {\
      type zero = {0};\
      return zero;\
    }\
\
    return n->value;\
  }\
\
  void type##_insert(type##_bst* b, type value) {\
    if (b == NULL)\
      return;\
\
    if (b->size == 0) {\
      b->root->value = value;\
\
      b->size++;\
\
      return;\
    }\
\
    type##_bstNode* trav = b->root;\
    while (trav != NULL) {\
      if (value == trav->value)\
        return;\
      else if (value < trav->value) {\
        if (trav->left != NULL)\
          trav = trav->left;\
        else {\
          type##_bstNode* new_node = (type##_bstNode*)malloc(sizeof(type##_bstNode));\
          new_node->value = value;\
          new_node->parent = trav;\
          trav->left = new_node;\
\
          b->size++;\
\
          return;\
        }\
      }\
      else if (value > trav->value) {\
        if (trav->right != NULL)\
          trav = trav->right;\
        else {\
          type##_bstNode* new_node = (type##_bstNode*)malloc(sizeof(type##_bstNode));\
          new_node->value = value;\
          new_node->parent = trav;\
          trav->right = new_node;\
\
          b->size++;\
\
          return;\
        }\
      }\
    }\
  }\
\
  void type##_erase(type##_bst* b, type value) {\
    if (b == NULL)\
      return;\
\
    if (b->size == 0)\
      return;\
    if (b->size == 1) {\
      b->size--;\
\
      return;\
    }\
\
    type##_bstNode* trav = b->root;\
    while (trav != NULL) {\
      if (value == trav->value) {\
        type##_bstNode* to_delete = trav;\
        if (trav->right != NULL) {\
          trav = trav->right;\
          while (trav->left != NULL)\
            trav = trav->left;\
        }\
        if (trav->left != NULL) {\
          trav = trav->left;\
          while (trav->right != NULL)\
            trav = trav->right;\
        }\
        if (trav->right != NULL) {\
          to_delete->value = trav->value;\
          trav->parent->left = trav->right;\
          trav->right->parent = trav->parent;\
          free(trav);\
          trav = NULL;\
\
          b->size--;\
\
          return;\
        }\
        if (trav->left != NULL) {\
          to_delete->value = trav->value;\
          trav->parent->right = trav->left;\
          trav->left->parent = trav->parent;\
          free(trav);\
          trav = NULL;\
\
          b->size--;\
\
          return;\
        }\
        if (trav->left == NULL && trav->right == NULL) {\
          to_delete->value = trav->value;\
          if (trav->parent->left == trav)\
            trav->parent->left = NULL;\
          if (trav->parent->right == trav)\
            trav->parent->right = NULL;\
          free(trav);\
          trav = NULL;\
\
          b->size--;\
        }\
      }\
      else if(value < trav->value)\
        trav = trav->left;\
      else if(value > trav->value)\
        trav = trav->right;\
    }\
  }\
\
  int64_t type##_size(type##_bst* b) {\
    if (b == NULL)\
      return -1;\
\
    return b->size;\
  }\
\
  int8_t type##_empty(type##_bst* b) {\
    if (b == NULL)\
      return -1;\
\
    return b->size == 0;\
  }

#define BUILD_BST(b, type)\
  b._initialize = type##_initialize;\
  b._dispose = type##_dispose;\
  b._get_first_node = type##_get_first_node;\
  b._get_last_node = type##_get_last_node;\
  b._get_node = type##_get_node;\
  b._next_node = type##_next_node;\
  b._prev_node = type##_prev_node;\
  b._node_value = type##_node_value;\
  b._insert = type##_insert;\
  b._erase = type##_erase;\
  b._size = type##_size;\
  b._empty = type##_empty;

#endif

#ifndef AVLTREE_H
#define AVLTREE_H
#include <stdlib.h>
#include <stdint.h>

#define CREATE_AVL(type)                                                                                  \
                                                                                                          \
  typedef struct type##_avlNode {                                                                         \
                                                                                                          \
    type                   value;                                                                         \
    struct type##_avlNode* parent;                                                                        \
    struct type##_avlNode* left;                                                                          \
    struct type##_avlNode* right;                                                                         \
    uint32_t               height;                                                                        \
  } type##_avlNode;                                                                                       \
                                                                                                          \
  typedef struct type##_avl {                                                                             \
                                                                                                          \
    type##_avlNode* root;                                                                                 \
    uint32_t        size;                                                                                 \
  } type##_avl;                                                                                           \
                                                                                                          \
  void type##_inorder_delete(type##_avl* a, type##_avlNode* r) {                                          \
    if (a == NULL || r == NULL)                                                                           \
      return;                                                                                             \
                                                                                                          \
    type##_inorder_delete(a, r->left);                                                                    \
    type##_inorder_delete(a, r->right);                                                                   \
    if (r != NULL)                                                                                        \
      free(r);                                                                                            \
    r = NULL;                                                                                             \
  }                                                                                                       \
                                                                                                          \
  void type##_initialize(type##_avl* a) {                                                                 \
    if (a == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    a->size = 0;                                                                                          \
                                                                                                          \
    a->root = malloc(sizeof(type##_avlNode));                                                             \
  }                                                                                                       \
                                                                                                          \
  void type##_dispose(type##_avl* a) {                                                                    \
    if (a == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    type##_inorder_delete(a, a->root);                                                                    \
  }                                                                                                       \
                                                                                                          \
  type##_avlNode* type##_get_first_node(type##_avl* a) {                                                  \
    if (a == NULL)                                                                                        \
      return NULL;                                                                                        \
                                                                                                          \
    type##_avlNode* trav = a->root;                                                                       \
    while (trav->left != NULL)                                                                            \
      trav = trav->left;                                                                                  \
    return trav;                                                                                          \
  }                                                                                                       \
                                                                                                          \
  type##_avlNode* type##_get_last_node(type##_avl* a) {                                                   \
    if (a == NULL)                                                                                        \
      return NULL;                                                                                        \
                                                                                                          \
    type##_avlNode* trav = a->root;                                                                       \
    while (trav->right != NULL)                                                                           \
      trav = trav->right;                                                                                 \
    return trav;                                                                                          \
  }                                                                                                       \
                                                                                                          \
  type##_avlNode* type##_get_node(type##_avl* a, const type value) {                                      \
    if (a == NULL)                                                                                        \
      return NULL;                                                                                        \
                                                                                                          \
    type##_avlNode* trav = a->root;                                                                       \
    while (trav != NULL) {                                                                                \
      if (value == trav->value)                                                                           \
        return trav;                                                                                      \
      else if (value < trav->value && trav->left != NULL)                                                 \
        trav = trav->left;                                                                                \
      else if (value > trav->value && trav->right != NULL)                                                \
        trav = trav->right;                                                                               \
      else                                                                                                \
        return NULL;                                                                                      \
    }                                                                                                     \
    return NULL;                                                                                          \
  }                                                                                                       \
                                                                                                          \
  type##_avlNode* type##_next_node(type##_avl* a, type##_avlNode* n) {                                    \
    if (a == NULL || n == NULL)                                                                           \
      return NULL;                                                                                        \
                                                                                                          \
    type##_avlNode* trav = n;                                                                             \
    if (trav->right == NULL) {                                                                            \
      while (trav == trav->parent->right)                                                                 \
        trav = trav->parent;                                                                              \
      return trav->parent;                                                                                \
    }                                                                                                     \
    trav = trav->right;                                                                                   \
    while (trav->left != NULL)                                                                            \
      trav = trav->left;                                                                                  \
    return trav;                                                                                          \
  }                                                                                                       \
                                                                                                          \
  type##_avlNode* type##_prev_node(type##_avl* a, type##_avlNode* n) {                                    \
    if (a == NULL || n == NULL)                                                                           \
      return NULL;                                                                                        \
                                                                                                          \
    type##_avlNode* trav = n;                                                                             \
    if (trav->left == NULL) {                                                                             \
      while (trav == trav->parent->left)                                                                  \
        trav = trav->parent;                                                                              \
      return trav->parent;                                                                                \
    }                                                                                                     \
    trav = trav->left;                                                                                    \
    while (trav->right != NULL)                                                                           \
      trav = trav->right;                                                                                 \
    return trav;                                                                                          \
  }                                                                                                       \
                                                                                                          \
  type type##_node_value(type##_avl* a, type##_avlNode* n) {                                              \
    if (a == NULL || n == NULL) {                                                                         \
      type zero = {0};                                                                                    \
      return zero;                                                                                        \
    }                                                                                                     \
                                                                                                          \
    return n->value;                                                                                      \
  }                                                                                                       \
                                                                                                          \
  void type##_fix(type##_avl* a, type##_avlNode* n);                                                      \
                                                                                                          \
  void type##_insert(type##_avl* a, const type value) {                                                   \
    if (a == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    if (a->size == 0) {                                                                                   \
      a->root->value = value;                                                                             \
                                                                                                          \
      a->size++;                                                                                          \
                                                                                                          \
      return;                                                                                             \
    }                                                                                                     \
                                                                                                          \
    type##_avlNode* trav = a->root;                                                                       \
    while (trav != NULL) {                                                                                \
      if (value == trav->value)                                                                           \
        return;                                                                                           \
      if (value < trav->value) {                                                                          \
        if (trav->left != NULL)                                                                           \
          trav = trav->left;                                                                              \
        else {                                                                                            \
          type##_avlNode* new_node = malloc(sizeof(type##_avlNode));                                      \
          new_node->value = value;                                                                        \
          new_node->parent = trav;                                                                        \
          trav->left = new_node;                                                                          \
                                                                                                          \
          a->size++;                                                                                      \
                                                                                                          \
          return;                                                                                         \
        }                                                                                                 \
      }                                                                                                   \
      if (value > trav->value) {                                                                          \
        if (trav->right != NULL)                                                                          \
          trav = trav->right;                                                                             \
        else {                                                                                            \
          type##_avlNode* new_node = malloc(sizeof(type##_avlNode));                                      \
          new_node->value = value;                                                                        \
          new_node->parent = trav;                                                                        \
          trav->right = new_node;                                                                         \
                                                                                                          \
          a->size++;                                                                                      \
                                                                                                          \
          return;                                                                                         \
        }                                                                                                 \
      }                                                                                                   \
    }                                                                                                     \
  }                                                                                                       \
                                                                                                          \
  void type##_erase(type##_avl* a, const type value) {                                                    \
    if (a == NULL)                                                                                        \
      return;                                                                                             \
                                                                                                          \
    if (a->size == 0)                                                                                     \
      return;                                                                                             \
    if (a->size == 1) {                                                                                   \
      a->size--;                                                                                          \
                                                                                                          \
      return;                                                                                             \
    }                                                                                                     \
                                                                                                          \
    type##_avlNode* trav = a->root;                                                                       \
    while (trav != NULL) {                                                                                \
      if (value == trav->value) {                                                                         \
        type##_avlNode* to_delete = trav;                                                                 \
        if (trav->right != NULL) {                                                                        \
          trav = trav->right;                                                                             \
          while (trav->left != NULL)                                                                      \
            trav = trav->left;                                                                            \
        }                                                                                                 \
        if (trav->left != NULL) {                                                                         \
          trav = trav->left;                                                                              \
          while (trav->right != NULL)                                                                     \
            trav = trav->right;                                                                           \
        }                                                                                                 \
        if (trav->right != NULL) {                                                                        \
          to_delete->value = trav->value;                                                                 \
          trav->parent->left = trav->right;                                                               \
          trav->right->parent = trav->parent;                                                             \
          free(trav);                                                                                     \
          trav = NULL;                                                                                    \
                                                                                                          \
          a->size--;                                                                                      \
                                                                                                          \
          return;                                                                                         \
        }                                                                                                 \
        if (trav->left != NULL) {                                                                         \
          to_delete->value = trav->value;                                                                 \
          trav->parent->right = trav->left;                                                               \
          trav->left->parent = trav->parent;                                                              \
          free(trav);                                                                                     \
          trav = NULL;                                                                                    \
                                                                                                          \
          a->size--;                                                                                      \
                                                                                                          \
          return;                                                                                         \
        }                                                                                                 \
        if (trav->left == NULL && trav->right == NULL) {                                                  \
          to_delete->value = trav->value;                                                                 \
          if (trav->parent->left == trav)                                                                 \
            trav->parent->left = NULL;                                                                    \
          if (trav->parent->right == trav)                                                                \
            trav->parent->right = NULL;                                                                   \
          free(trav);                                                                                     \
          trav = NULL;                                                                                    \
                                                                                                          \
          a->size--;                                                                                      \
                                                                                                          \
          return;                                                                                         \
        }                                                                                                 \
      }                                                                                                   \
      else if(value < trav->value)                                                                        \
        trav = trav->left;                                                                                \
      else if(value > trav->value)                                                                        \
        trav = trav->right;                                                                               \
    }                                                                                                     \
  }                                                                                                       \
                                                                                                          \
  int64_t type##_size(type##_avl* a) {                                                                    \
    if (a == NULL)                                                                                        \
      return -1;                                                                                          \
                                                                                                          \
    return a->size;                                                                                       \
  }                                                                                                       \
                                                                                                          \
  int8_t type##_empty(type##_avl* a) {                                                                    \
    if (a == NULL)                                                                                        \
      return -1;                                                                                          \
                                                                                                          \
    return a->size == 0;                                                                                  \
  }

#define BUILD_AVL(a, type)                                                                                \
  a._initialize = type##_initialize;                                                                      \
  a._dispose = type##_dispose;                                                                            \
  a._get_first_node = type##_get_first_node;                                                              \
  a._get_last_node = type##_get_last_node;                                                                \
  a._get_node = type##_get_node;                                                                          \
  a._next_node = type##_next_node;                                                                        \
  a._prev_node = type##_prev_node;                                                                        \
  a._node_value = type##_node_value;                                                                      \
  a._insert = type##_insert;                                                                              \
  a._erase = type##_erase;                                                                                \
  a._size = type##_size;                                                                                  \
  a._empty = type##_empty;

#endif

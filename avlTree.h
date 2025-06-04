#ifndef AVLTREE_H
#define AVLTREE_H
#include <stdlib.h>
#include <stdint.h>

#define CREATE_AVL(type)\
\
  typedef struct type##_avlNode {\
\
    type                   value;\
    struct type##_avlNode* left;\
    struct type##_avlNode* right;\
    struct type##_avlNode* parent;\
  } type##_avlNode;\
\


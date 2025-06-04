#ifndef TREEROTATION_H
#define TREEROTATION_H

#define CREATE_TREEROTATION(type)                                       \
                                                                        \
  void type##_left_rotate(type* n) {                                    \
    if (n == NULL)                                                      \
      return;                                                           \
                                                                        \
    type* temp1 = n->left;                                              \
    type* temp2 = n->parent;                                            \
    type* temp3 = temp2->parent;                                        \
    if (temp2 != NULL)                                                  \
      temp2->right = temp1;                                             \
    if (temp1 != NULL)                                                  \
      temp1->parent = temp2;                                            \
    n->left = temp2;                                                    \
    if (temp2 != NULL)                                                  \
      temp2->parent = n;                                                \
    if (temp3 != NULL) {                                                \
      n->parent = temp3;                                                \
      if (temp3->left == temp2)                                         \
        temp3->left = n;                                                \
      if (temp3->right == temp2)                                        \
        temp3->right = n;                                               \
    }                                                                   \
  }                                                                     \
                                                                        \
  void type##_right_rotate(type* n) {                                   \
    if (n == NULL)                                                      \
      return;                                                           \
                                                                        \
    type* temp1 = n->right;                                             \
    type* temp2 = n->parent;                                            \
    type* temp3 = temp2->parent;                                        \
    if (temp2 != NULL)                                                  \
      temp2->left = temp1;                                              \
    if (temp1 != NULL)                                                  \
      temp1->parent = temp2;                                            \
    n->right = temp2;                                                   \
    if (temp2 != NULL)                                                  \
      temp2->parent = n;                                                \
    if (temp3 != NULL) {                                                \
      n->parent = temp3;                                                \
      if (temp3->left == temp2)                                         \
        temp3->left = n;                                                \
      if (temp3->right == temp2)                                        \
        temp3->right = n;                                               \
    }                                                                   \
  }

#endif

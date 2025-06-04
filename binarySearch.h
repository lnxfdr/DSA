#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H
#include <stdint.h>

#define CREATE_BINARYSEARCH(type)                                                                                               \
                                                                                                                                \
  int64_t type##_binary_search(type* arr, const uint32_t start, const uint32_t end, const type value) {                         \
    uint32_t left, right, middle;                                                                                               \
    left = start;                                                                                                               \
    right = end;                                                                                                                \
    while (left <= right) {                                                                                                     \
      middle = left + (right - left) / 2;                                                                                       \
      if (arr[middle] == value)                                                                                                 \
        return middle;                                                                                                          \
      if (arr[middle] < value)                                                                                                  \
        right = middle - 1;                                                                                                     \
      if (arr[middle] > value)                                                                                                  \
        left = middle + 1;                                                                                                      \
    }                                                                                                                           \
    return left;                                                                                                                \
  }

#endif

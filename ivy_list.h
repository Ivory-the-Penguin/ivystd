/*
  ----- Ivy List -----
  Version: 0.1.0
  License: MIT-0

  This is a header only library that has a generic list for the ivystd.
  Inspired by rxi's vec
*/

#ifndef IVY_LIST_H
#define IVY_LIST_H

#define IVY_LIST_MAJOR 0
#define IVY_LIST_MINOR 1
#define IVY_LIST_FIX 0

#include "ivy_allocator.h"
#include "ivy_core.h"

typedef struct {
  void *data;
  uint64_t length;
  uint64_t capacity;
  uint64_t item_size;
  allocator_t alloc;
} list_opaque_t;

#define LIST_MINIMUM_CAPACITY 16

#define list_t(type)    \
  struct {              \
    type *data;         \
    uint64_t length;    \
    uint64_t capacity;  \
    uint64_t item_size; \
    allocator_t alloc;  \
  }

#define list_init(list_ptr, allocator)                                         \
  do {                                                                         \
    (list_ptr)->item_size = sizeof(*(list_ptr)->data);                         \
    (list_ptr)->data =                                                         \
        ivy_alloc((allocator), (list_ptr)->item_size * LIST_MINIMUM_CAPACITY); \
    (list_ptr)->length = 0;                                                    \
    (list_ptr)->capacity = LIST_MINIMUM_CAPACITY;                              \
    (list_ptr)->alloc = (allocator);                                           \
  } while (0)

#endif

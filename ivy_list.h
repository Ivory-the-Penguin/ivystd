/*
  ----- Ivy List -----
  Version: 0.3.0
  License: MIT-0

  This is a header only library that has a generic list for the ivystd.
  Inspired by rxi's vec
*/

#ifndef IVY_LIST_H
#define IVY_LIST_H

#include <stdbool.h>
#define IVY_LIST_MAJOR 0
#define IVY_LIST_MINOR 3
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

IVY_FORCE_INLINE void list_expand(list_opaque_t *list, uint64_t new_size) {
  uint64_t aligned = align_bytes(new_size);

  IVY_ASSERT(list->capacity < aligned,
             "New size has to be bigger than the old one");

  list->data =
      ivy_realloc(list->alloc, (void *)list->data, aligned * list->item_size);
  list->capacity = aligned;
}

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

#define list_free(list_ptr)                        \
  do {                                             \
    (list_ptr)->length = 0;                        \
    (list_ptr)->capacity = 0;                      \
    (list_ptr)->item_size = 0;                     \
    ivy_free((list_ptr)->alloc, (list_ptr)->data); \
    (list_ptr)->data = NULL;                       \
    (list_ptr)->alloc = (allocator_t){0};          \
  } while (0)

#endif

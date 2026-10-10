/*
  ----- Ivy List -----
  Version: 0.5.1
  License: MIT-0

  This is a header only library that has a generic list for the ivystd.
  Inspired by rxi's vec
*/

#ifndef IVY_LIST_H
#define IVY_LIST_H

#define IVY_LIST_MAJOR 0
#define IVY_LIST_MINOR 5
#define IVY_LIST_FIX 1

#include "ivy_allocator.h"
#include "ivy_core.h"

typedef struct {
  void *data;
  u64 length;
  u64 capacity;
  u64 item_size;
  allocator_t alloc;
} list_opaque_t;

#define LIST_MINIMUM_CAPACITY 16

IVY_FORCE_INLINE void list_expand(list_opaque_t *list, u64 new_size) {
  u64 aligned = align_bytes(new_size);

  IVY_ASSERT(list->capacity < aligned,
             "New size has to be bigger than the old one");

  list->data =
      ivy_realloc(list->alloc, (void *)list->data, aligned * list->item_size);
  list->capacity = aligned;
}

#define list_t(type)   \
  struct {             \
    type *data;        \
    u64 length;        \
    u64 capacity;      \
    u64 item_size;     \
    allocator_t alloc; \
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

#define list_init_cap(list_ptr, allocator, cap)                             \
  do {                                                                      \
    (list_ptr)->item_size = sizeof(*(list_ptr)->data);                      \
    (list_ptr)->data =                                                      \
        ivy_alloc((allocator), (list_ptr)->item_size * align_bytes((cap))); \
    (list_ptr)->length = 0;                                                 \
    (list_ptr)->capacity = align_bytes((cap));                              \
    (list_ptr)->alloc = (allocator);                                        \
  } while (0)

#define list_push(list_ptr, item)                                         \
  do {                                                                    \
    if ((list_ptr)->length + 1 > (list_ptr)->capacity) {                  \
      list_expand((list_opaque_t *)(list_ptr), (list_ptr)->capacity * 2); \
    }                                                                     \
                                                                          \
    (list_ptr)->data[(list_ptr)->length++] = item;                        \
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

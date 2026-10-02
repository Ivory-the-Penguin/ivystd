// You can't change the default allocators for the heap.
// BUT you can just make another allocator
#ifndef IVY_ALLOCATOR_H
#define IVY_ALLOCATOR_H

#include "ivy_assert.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define ALIGN_BYTES(bytes) (uint64_t)(((bytes) + 15) & ~15)

#define ALLOC(allocator, size)                                                 \
  (IVY_ASSERT(allocator_has_flag((allocator), ALLOCATOR_HAS_ALLOC),            \
              "Allocator doesn't have ALLOC capability"),                      \
   (allocator).alloc(&(allocator), (size)))

#define REALLOC(allocator, ptr, new_size)                                      \
  (IVY_ASSERT(allocator_has_flag((allocator), ALLOCATOR_HAS_REALLOC),          \
              "Allocator doesn't have REALLOC capability"),                    \
   (allocator).realloc(&(allocator), (ptr), (new_size)))
#define FREE(allocator, ptr)                                                   \
  (allocator_has_flag((allocator), ALLOCATOR_HAS_FREE)                         \
       ? (allocator).free(&(allocator), (ptr))                                 \
       : (void)0)

typedef enum {
  ALLOCATOR_HAS_ALLOC = 1 << 0,
  ALLOCATOR_HAS_REALLOC = 1 << 1,
  ALLOCATOR_HAS_FREE = 1 << 2,
} allocator_flag_t;

typedef struct allocator_t {
  void *ctx;
  allocator_flag_t flags;

  void *(*alloc)(struct allocator_t *self, uint64_t size);
  void *(*realloc)(struct allocator_t *self, void *ptr, uint64_t new_size);
  void (*free)(struct allocator_t *self, void *ptr);
} allocator_t;

static inline bool allocator_has_flag(allocator_t alloc,
                                      allocator_flag_t flag) {
  return (alloc.flags & flag) > 0;
}

static inline void *_heap_alloc(allocator_t *self, uint64_t size) {
  (void)self;
  IVY_ASSERT(size > 0, "Size can't be zero");
  return malloc(((uint64_t)size));
}

static inline void *_heap_realloc(allocator_t *self, void *ptr,
                                  uint64_t new_size) {
  (void)self;
  return realloc(ptr, new_size);
}

static inline void _heap_free(allocator_t *self, void *ptr) {
  (void)self;
  IVY_ASSERT(ptr != NULL, "Pointer can't be uninitialized or already freed");
  free(ptr);
}

extern allocator_t heap;

#ifdef IVY_IMPL

allocator_t heap = (allocator_t){
    .ctx = NULL,
    .flags = ALLOCATOR_HAS_ALLOC | ALLOCATOR_HAS_REALLOC | ALLOCATOR_HAS_FREE,
    .alloc = _heap_alloc,
    .realloc = _heap_realloc,
    .free = _heap_free,
};

#endif

#endif
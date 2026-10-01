// You can't change the default allocators for the heap.
// BUT you can just make another allocator
#ifndef IVY_STD_ALLOCATOR_H
#define IVY_STD_ALLOCATOR_H

#include "assert.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define ALIGN_BYTES(bytes) (uint64_t)(((bytes) + 7) & ~7)

#define ALLOC(allocator, size) (allocator).alloc(&(allocator), (size))
#define REALLOC(allocator, ptr, new_size)                                      \
  (allocator).realloc(&(allocator), (ptr), (size))
#define FREE(allocator, ptr) (allocator).free(&(allocator), (ptr))

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

static allocator_t heap = (allocator_t){
    .ctx = NULL,
    .flags = ALLOCATOR_HAS_ALLOC | ALLOCATOR_HAS_REALLOC | ALLOCATOR_HAS_FREE,
    .alloc = _heap_alloc,
    .free = _heap_free,
};

#endif
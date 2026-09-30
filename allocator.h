// You can't change the default allocators for the heap.
// BUT you can just make another allocator
#ifndef IVY_STD_ALLOCATOR_H
#define IVY_STD_ALLOCATOR_H

#include <stdint.h>
#include <stdlib.h>

#define ALIGN_BYTES(bytes) (uint64_t)(((bytes) + 7) & ~7)

#define ALLOC(allocator, bytes) (allocator).alloc(&(allocator), (bytes))
#define FREE(allocator, ptr) (allocator).free(&(allocator), (ptr))

typedef struct allocator_t {
  void *ctx;

  void *(*alloc)(struct allocator_t *self, uint64_t bytes);
  void (*free)(struct allocator_t *self, void *ptr);
} allocator_t;

static inline void *_heap_alloc(allocator_t *self, uint64_t bytes) {
  (void)self;
  return malloc(((uint64_t)bytes));
}

static inline void _heap_free(allocator_t *self, void *ptr) {
  (void)self;
  free(ptr);
}

static allocator_t heap = (allocator_t){
    .ctx = NULL,
    .alloc = _heap_alloc,
    .free = _heap_free,
};

#endif
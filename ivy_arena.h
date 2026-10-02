#ifndef IVY_ARENA_H
#define IVY_ARENA_H

#include <stdint.h>
#include <string.h>

#include "ivy_allocator.h"
#include "ivy_assert.h"

typedef struct {
  uint8_t *buffer;
  uint64_t offset;
  uint64_t capacity;
} arena_t;

static inline arena_t arena_make(uint8_t *buffer, uint64_t n) {
  memset(buffer, 0, n);
  return (arena_t){
      .buffer = buffer,
      .offset = 0,
      .capacity = n,
  };
}

static inline void *_arena_alloc(allocator_t *self, uint64_t bytes) {
  arena_t *ctx = (arena_t *)self->ctx;

  uint64_t aligned_bytes = ALIGN_BYTES(bytes);

  IVY_ASSERT(ctx->offset + aligned_bytes <= ctx->capacity,
             "Arena ran out of memory!");

  ctx->offset += aligned_bytes;

  return ctx->buffer + ctx->offset - aligned_bytes;
}

static inline allocator_t arena_make_allocator(arena_t *arena) {
  return (allocator_t){
      .ctx = (void *)arena,
      .flags = ALLOCATOR_HAS_ALLOC,
      .alloc = _arena_alloc,
  };
}

static inline void arena_clear(arena_t *arena) {
  memset(arena->buffer, 0, arena->offset);
  arena->offset = 0;
}

#endif
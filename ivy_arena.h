/*
  ----- Ivy Arena -----
  Version: 0.1.0
  License: MIT-0

  This header only library has an arena type for the ivystd.
  Inspired by Zig's FixedBufferAllocator.
*/

#ifndef IVY_ARENA_H
#define IVY_ARENA_H

#define IVY_ARENA_MAJOR 0
#define IVY_ARENA_MINOR 1
#define IVY_ARENA_FIX 0

#include "ivy_allocator.h"
#include "ivy_core.h"

typedef struct {
  uint8_t *buffer;
  uint64_t offset;
  uint64_t capacity;
} arena_t;

IVY_FORCE_INLINE arena_t arena_make(uint8_t *buffer, uint64_t n) {
  memset(buffer, 0, n);
  return (arena_t){
      .buffer = buffer,
      .offset = 0,
      .capacity = n,
  };
}

IVY_FORCE_INLINE void *_arena_alloc(allocator_t *self, uint64_t bytes) {
  arena_t *ctx = (arena_t *)self->ctx;

  uint64_t aligned_bytes = align_bytes(bytes);

  IVY_ASSERT(ctx->offset + aligned_bytes <= ctx->capacity,
             "Arena ran out of memory!");

  ctx->offset += aligned_bytes;

  return ctx->buffer + ctx->offset - aligned_bytes;
}

IVY_FORCE_INLINE allocator_t arena_make_allocator(arena_t *arena) {
  return (allocator_t){
      .ctx = (void *)arena,
      .flags = ALLOCATOR_HAS_ALLOC,
      .alloc = _arena_alloc,
  };
}

IVY_FORCE_INLINE void arena_clear(arena_t *arena) {
  memset(arena->buffer, 0, arena->offset);
  arena->offset = 0;
}

#endif

/*
  ----- Ivy Arena -----
  Version: 1.1.0
  License: MIT-0

  This header only library has an arena allocator for the ivystd.
  Inspired by Zig's Arena.
*/

#ifndef IVY_ARENA_H
#define IVY_ARENA_H

#define IVY_ARENA_MAJOR 1
#define IVY_ARENA_MINOR 1
#define IVY_ARENA_FIX 0

#include "ivy_allocator.h"
#include "ivy_core.h"

typedef struct {
  uint8_t **chunks;
  uint64_t offset;
  uint64_t cur_chunk;
  uint64_t chunks_length;
  uint64_t chunks_capacity;
  allocator_t alloc;
} arena_t;

#define ARENA_CHUNK_SIZE (1024 * 4)

IVY_FORCE_INLINE arena_t arena_make(allocator_t alloc) {
  arena_t arena = {0};
  arena.chunks = ivy_alloc(heap, sizeof(uint8_t *));
  arena.chunks[0] = ivy_alloc(alloc, ARENA_CHUNK_SIZE);
  memset(arena.chunks[0], 0, ARENA_CHUNK_SIZE);
  arena.offset = 0;
  arena.cur_chunk = 0;
  arena.chunks_length = 1;
  arena.chunks_capacity = 1;
  arena.alloc = alloc;
  return arena;
}

IVY_FORCE_INLINE void *_arena_alloc(allocator_t *self, uint64_t bytes) {
  arena_t *ctx = (arena_t *)self->ctx;

  IVY_ASSERT(ctx->alloc.alloc != NULL, "Arena is already freed");

  uint64_t aligned_bytes = align_bytes(bytes);

  IVY_ASSERT(aligned_bytes <= ARENA_CHUNK_SIZE,
             "Memory too big, use heap instead");

  if (ctx->offset + aligned_bytes > ARENA_CHUNK_SIZE) {
    if (ctx->chunks_length + 1 > ctx->chunks_capacity) {
      ctx->chunks_capacity *= 2;
      ctx->chunks = ivy_realloc(heap, ctx->chunks,
                                sizeof(uint8_t *) * ctx->chunks_capacity);
    }
    ctx->chunks[++ctx->cur_chunk] = ivy_alloc(ctx->alloc, ARENA_CHUNK_SIZE);
    memset(ctx->chunks[ctx->cur_chunk], 0, ARENA_CHUNK_SIZE);
    ctx->chunks_length++;
    ctx->offset = 0;
  }

  ctx->offset += aligned_bytes;

  return ctx->chunks[ctx->cur_chunk] + ctx->offset - aligned_bytes;
}

IVY_FORCE_INLINE allocator_t arena_make_allocator(arena_t *arena) {
  return (allocator_t){
      .ctx = (void *)arena,
      .flags = ALLOCATOR_HAS_ALLOC,
      .alloc = _arena_alloc,
  };
}

// Just resets it, doesn't clear memory
IVY_FORCE_INLINE void arena_reset(arena_t *arena) {
  arena->offset = 0;
  arena->cur_chunk = 0;
}

// Zeroes out the memory
IVY_FORCE_INLINE void arena_clear(arena_t *arena) {
  for (uint64_t i = 0; i <= arena->cur_chunk; i++) {
    memset(arena->chunks[i], 0, ARENA_CHUNK_SIZE);
  }
  arena_reset(arena);
}

IVY_FORCE_INLINE void arena_free(arena_t *arena) {
  for (uint64_t i = 0; i < arena->chunks_length; i++) {
    ivy_free(arena->alloc, arena->chunks[i]);
  }

  ivy_free(heap, arena->chunks);

  *arena = (arena_t){0};
}

#endif

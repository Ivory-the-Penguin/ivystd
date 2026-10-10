/*
  ----- Ivy Arena -----
  Version: 1.2.1
  License: MIT-0

  This header only library has an arena allocator for the ivystd.
  Inspired by Zig's Arena.
*/

#ifndef IVY_ARENA_H
#define IVY_ARENA_H

#define IVY_ARENA_MAJOR 1
#define IVY_ARENA_MINOR 2
#define IVY_ARENA_FIX 1

#include "ivy_allocator.h"
#include "ivy_core.h"
#include "ivy_list.h"

typedef list_t(u8 *) chunk_list_t;

typedef struct {
  chunk_list_t chunks;
  u64 offset;
  u64 cur_chunk;
  allocator_t alloc;
} arena_t;

#define ARENA_CHUNK_SIZE (1024 * 4)

IVY_FORCE_INLINE arena_t arena_make(allocator_t alloc) {
  arena_t arena = {0};
  arena.offset = 0;
  arena.cur_chunk = 0;
  arena.alloc = alloc;

  list_init(&arena.chunks, heap);
  list_push(&arena.chunks, ivy_alloc(alloc, ARENA_CHUNK_SIZE));
  memset(arena.chunks.data[0], 0, ARENA_CHUNK_SIZE);

  return arena;
}

IVY_FORCE_INLINE void *_arena_alloc(allocator_t *self, u64 bytes) {
  arena_t *ctx = (arena_t *)self->ctx;

  IVY_ASSERT(ctx->alloc.alloc != NULL, "Arena is already freed");

  u64 aligned_bytes = align_bytes(bytes);

  IVY_ASSERT(aligned_bytes <= ARENA_CHUNK_SIZE,
             "Memory too big, use heap instead");

  if (ctx->offset + aligned_bytes > ARENA_CHUNK_SIZE) {
    list_push(&ctx->chunks, ivy_alloc(ctx->alloc, ARENA_CHUNK_SIZE));
    ctx->cur_chunk++;
    memset(ctx->chunks.data[ctx->cur_chunk], 0, ARENA_CHUNK_SIZE);
    ctx->offset = 0;
  }

  ctx->offset += aligned_bytes;

  return ctx->chunks.data[ctx->cur_chunk] + ctx->offset - aligned_bytes;
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
  LIST_FOREACH(&arena->chunks, i, 0) {
    memset(arena->chunks.data[i], 0, ARENA_CHUNK_SIZE);
  }
  arena_reset(arena);
}

IVY_FORCE_INLINE void arena_free(arena_t *arena) {
  for (u64 i = 0; i < arena->chunks.length; i++) {
    ivy_free(arena->alloc, arena->chunks.data[i]);
  }

  list_free(&arena->chunks);

  *arena = (arena_t){0};
}

#endif

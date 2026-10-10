/*
  ----- Ivy Fixed Buffer -----
  Version: 1.1.1
  License: MIT-0

  This header only library has a fixed buffer allocator for the ivystd.
  Inspired by Zig's FixedBufferAllocator.
*/

#ifndef IVY_FB_H
#define IVY_FB_H

#define IVY_FB_MAJOR 1
#define IVY_FB_MINOR 1
#define IVY_FB_FIX 1

#include "ivy_allocator.h"
#include "ivy_core.h"

typedef struct {
  u8 *buffer;
  u64 offset;
  u64 capacity;
} fixed_buffer_t;

IVY_FORCE_INLINE fixed_buffer_t fb_make(u8 *buffer, u64 n) {
  memset(buffer, 0, n);
  return (fixed_buffer_t){
      .buffer = buffer,
      .offset = 0,
      .capacity = n,
  };
}

IVY_FORCE_INLINE void *_fb_alloc(allocator_t *self, u64 bytes) {
  fixed_buffer_t *ctx = (fixed_buffer_t *)self->ctx;

  u64 aligned_bytes = align_bytes(bytes);

  IVY_ASSERT(ctx->offset + aligned_bytes <= ctx->capacity,
             "Fixed buffer ran out of memory!");

  ctx->offset += aligned_bytes;

  return ctx->buffer + ctx->offset - aligned_bytes;
}

IVY_FORCE_INLINE allocator_t fb_make_allocator(fixed_buffer_t *fb) {
  return (allocator_t){
      .ctx = (void *)fb,
      .flags = ALLOCATOR_HAS_ALLOC,
      .alloc = _fb_alloc,
  };
}

// Just resets it, doesn't clear memory
IVY_FORCE_INLINE void fb_reset(fixed_buffer_t *fb) { fb->offset = 0; }

// Zeroes out memory
IVY_FORCE_INLINE void fb_clear(fixed_buffer_t *fb) {
  memset(fb->buffer, 0, fb->offset);
  fb_reset(fb);
}

#endif

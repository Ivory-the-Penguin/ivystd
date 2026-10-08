/*
  ----- Ivy Fixed Buffer -----
  Version: 0.1.0
  License: MIT-0

  This header only library has a fixed buffer allocator for the ivystd.
  Inspired by Zig's FixedBufferAllocator.
*/

#ifndef IVY_FB_H
#define IVY_FB_H

#define IVY_FB_MAJOR 0
#define IVY_FB_MINOR 1
#define IVY_FB_FIX 0

#include "ivy_allocator.h"
#include "ivy_core.h"

typedef struct {
  uint8_t *buffer;
  uint64_t offset;
  uint64_t capacity;
} fixed_buffer_t;

IVY_FORCE_INLINE fixed_buffer_t fb_make(uint8_t *buffer, uint64_t n) {
  memset(buffer, 0, n);
  return (fixed_buffer_t){
      .buffer = buffer,
      .offset = 0,
      .capacity = n,
  };
}

IVY_FORCE_INLINE void *_fb_alloc(allocator_t *self, uint64_t bytes) {
  fixed_buffer_t *ctx = (fixed_buffer_t *)self->ctx;

  uint64_t aligned_bytes = align_bytes(bytes);

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

IVY_FORCE_INLINE void fb_clear(fixed_buffer_t *fb) {
  memset(fb->buffer, 0, fb->offset);
  fb->offset = 0;
}

#endif

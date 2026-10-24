/*
 *  ----- Ivy Fixed Buffer -----
 *  Version: 1.0.0
 *  License: MIT-0
 */

#ifndef IVY_FIXED_BUFFER_HPP_
#define IVY_FIXED_BUFFER_HPP_

#include "allocator.hpp"
#include "core.hpp"

namespace ivy {

struct fixed_buffer {
  u8 *buffer;
  u64 offset;
  const u64 capacity;

  ivy_forceinline static fixed_buffer make(u8 *buffer, u64 n) {
    return (fixed_buffer){
        .buffer = buffer,
        .offset = 0,
        .capacity = n,
    };
  }

  ivy_forceinline void reset() { this->offset = 0; }

  ivy_forceinline void clear() {
    memset(this->buffer, 0, this->offset);
    this->reset();
  }

  static void *_alloc(allocator *self, u64 size) {
    fixed_buffer *ctx = (fixed_buffer *)self->ctx;

    u64 aligned = align_bytes(size);

    ctx->offset += aligned;

    return &ctx->buffer[ctx->offset - aligned];
  }

  allocator alloc() {
    return (allocator){
        .ctx = this,
        .flags = ALLOCFLAGS_HAS_ALLOC,
        .alloc_cb = _alloc,
        .realloc_cb = nullptr,
        .free_cb = nullptr,
    };
  }
};

}  // namespace ivy

#endif  // IVY_FIXED_BUFFER_HPP_

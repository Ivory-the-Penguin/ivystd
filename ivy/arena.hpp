/*
 *  ----- Ivy Arena -----
 *  Version: 1.0.0
 *  License: MIT-0
 */

#ifndef IVY_ARENA_HPP_
#define IVY_ARENA_HPP_

#include "allocator.hpp"
#include "core.hpp"
#include "heap.hpp"
#include "list.hpp"

namespace ivy {

struct arena {
  list<u8 *> chunks;
  list<void *> big_chunks;
  u64 offset;
  u64 current_chunk;
  allocator alloc;

  static constexpr u64 chunk_size = 1024 * 4;

  // capacity is the amount of chunks we would have
  inline static arena make(allocator &alloc, u64 capacity) {
    arena out;
    out.chunks = list<u8 *>::make(heap, capacity);
    for (u64 i = 0; i < capacity; i++) {
      out.chunks.push((u8 *)alloc.alloc(chunk_size * sizeof(u8)));
    }
    out.big_chunks = list<void *>::make(heap);
    out.offset = 0;
    out.current_chunk = 0;
    out.alloc = alloc;
    return out;
  }

  ivy_forceinline static arena make(allocator &alloc) { return make(alloc, 1); }

  static inline void *_alloc(allocator &self, u64 size) {
    arena *ctx = (arena *)self.ctx;

    u64 aligned = align_bytes(size);

    if (aligned > chunk_size) {
      ctx->big_chunks.push(ctx->alloc.alloc(aligned));
      return ctx->big_chunks[ctx->big_chunks.length - 1];
    }

    if (ctx->offset + aligned > chunk_size) {
      ctx->chunks.push((u8 *)ctx->alloc.alloc(chunk_size));
      ctx->current_chunk++;
      ctx->offset = 0;
    }

    ctx->offset += aligned;

    return &ctx->chunks[ctx->current_chunk][ctx->offset - aligned];
  }

  inline void reset() {
    for (auto i : this->big_chunks) {
      this->alloc.free(i);
    }
    this->big_chunks.clear();

    this->offset = 0;
    this->current_chunk = 0;
  }

  inline void free() {
    this->reset();
    this->big_chunks.free();

    for (auto i : this->chunks) {
      this->alloc.free(i);
    }
    this->chunks.free();
  }

  inline allocator make_allocator() {
    return allocator{
        .ctx = this,
        .flags = ALLOCFLAGS_HAS_ALLOC,

        .alloc_cb = _alloc,
        .realloc_cb = nullptr,
        .free_cb = nullptr,
    };
  }
};

}  // namespace ivy

#endif  // IVY_ARENA_HPP_

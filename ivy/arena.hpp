/*
 *  ----- Ivy Arena -----
 *  Version: 0.4.1
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

  inline void reset() {
    for (auto i : this->big_chunks) {
      this->alloc.free(i);
    }
    this->big_chunks.clear();

    this->offset = 0;
    this->current_chunk = 0;
  }
};

}  // namespace ivy

#endif  // IVY_ARENA_HPP_

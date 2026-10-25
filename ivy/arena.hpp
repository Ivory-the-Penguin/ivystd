/*
 *  ----- Ivy Arena -----
 *  Version: 0.2.0
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

  static arena make(allocator alloc) {
    arena out;
    out.chunks = list<u8 *>::make(heap);
    out.chunks.push((u8 *)alloc.alloc(chunk_size));
    out.big_chunks = list<void *>::make(heap);
    out.offset = 0;
    out.current_chunk = 0;
    out.alloc = alloc;
    return out;
  }
};

}  // namespace ivy

#endif  // IVY_ARENA_HPP_

/*
 *  ----- Ivy Allocator -----
 *  Version: 1.1.1
 *  License: MIT-0
 */

#ifndef IVY_ALLOCATOR_HPP_
#define IVY_ALLOCATOR_HPP_

#include "core.hpp"

namespace ivy {

enum alloc_flags : u8 {
  ALLOCFLAGS_HAS_ALLOC = 1 << 0,
  ALLOCFLAGS_HAS_REALLOC = 1 << 1,
  ALLOCFLAGS_HAS_FREE = 1 << 2,
};

ivy_forceinline u64 align_bytes(u64 bytes) { return (u64)((bytes + 7) & ~7); }

struct allocator;

using alloc_fn = void *(*)(allocator * self, u64 size);
using realloc_fn = void *(*)(allocator * self, void *ptr, u64 new_size);
using free_fn = void (*)(allocator *self, void *ptr);

struct allocator {
  void *ctx;
  u8 flags;

  alloc_fn alloc_cb;
  realloc_fn realloc_cb;
  free_fn free_cb;

  ivy_forceinline void *alloc(u64 size) { return this->alloc_cb(this, size); }
  ivy_forceinline void free(void *ptr) { return this->free_cb(this, ptr); }
  ivy_forceinline void *realloc(void *ptr, u64 new_size) {
    return this->realloc_cb(this, ptr, new_size);
  }

  ivy_forceinline bool has_flag(alloc_flags flag) {
    return (this->flags & flag) > 0;
  }
};

}  // namespace ivy

#endif  // IVY_ALLOCATOR_HPP_

/*
 * ----- Ivy Alloc -----
 *  Version: 1.0.0
 *  License: MIT-0
 */

#ifndef IVY_ALLOC_H_
#define IVY_ALLOC_H_

#include "core.hpp"

namespace ivy {

enum alloc_flags : u8 {
  ALLOCFLAGS_HAS_ALLOC = 1 << 0,
  ALLOCFLAGS_HAS_REALLOC = 1 << 1,
  ALLOCFLAGS_HAS_FREE = 1 << 2,
};

ivy_forceinline u64 align_bytes(u64 bytes) { return (u64)((bytes + 15) & ~15); }

struct allocator;

using alloc_fn = void *(*)(allocator * self, u64 size);
using realloc_fn = void *(*)(allocator * self, void *ptr, u64 new_size);
using free_fn = void (*)(allocator *self, void *ptr);

struct allocator {
  void *ctx;
  alloc_flags flags;

  alloc_fn alloc_cb;
  realloc_fn realloc_cb;
  free_fn free_cb;

  void *alloc(u64 size) { return this->alloc_cb(this, size); }
  void free(void *ptr) { return this->free_cb(this, ptr); }
  void *realloc(void *ptr, u64 new_size) {
    return this->realloc_cb(this, ptr, new_size);
  }

  bool has_flag(alloc_flags flag) { return (this->flags & flag) > 0; }
};

}  // namespace ivy

#endif  // IVY_ALLOC_H_

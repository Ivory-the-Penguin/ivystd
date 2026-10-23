/*
 *  ----- Ivy Heap -----
 *  Version: 1.0.0
 *  License: MIT-0
 */

#ifndef IVY_HEAP_H_
#define IVY_HEAP_H_

#include <cstdlib>

#include "alloc.hpp"
#include "core.hpp"

namespace ivy {

ivy_forceinline void *_heap_alloc(allocator *self, u64 size) {
  (void)self;
  return std::malloc(size);
}

ivy_forceinline void *_heap_realloc(allocator *self, void *ptr, u64 new_size) {
  (void)self;
  return std::realloc(ptr, new_size);
}

ivy_forceinline void _heap_free(allocator *self, void *ptr) {
  (void)self;
  std::free(ptr);
}

inline allocator heap = (allocator){
    .ctx = nullptr,
    .flags =
        ALLOCFLAGS_HAS_ALLOC | ALLOCFLAGS_HAS_REALLOC | ALLOCFLAGS_HAS_FREE,

    .alloc_cb = _heap_alloc,
    .realloc_cb = _heap_realloc,
    .free_cb = _heap_free,
};

}  // namespace ivy

#endif  // IVY_HEAP_H_

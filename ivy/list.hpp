/*
 *  ----- Ivy List -----
 *  Version: 0.5.1
 *  License: MIT-0
 */

#ifndef IVY_LIST_HPP_
#define IVY_LIST_HPP_

#include "allocator.hpp"
#include "core.hpp"

namespace ivy {

template <typename T>
struct list {
  T *data;
  u64 length;
  u64 capacity;
  allocator alloc;

  static constexpr u64 minimum_capacity = 8;

  ivy_forceinline static list make(allocator alloc) {
    return make(alloc, minimum_capacity);
  }

  ivy_forceinline static list make(allocator alloc, u64 capacity) {
    const u64 aligned = align_bytes(capacity);

    return list{
        .data = (T *)alloc.alloc(aligned * sizeof(T)),
        .length = 0,
        .capacity = aligned,
        .alloc = alloc,
    };
  }

  ivy_forceinline void free() {
    this->alloc.free(this->data);
    this->length = 0;
    this->capacity = 0;
    this->alloc = allocator{};
  }

  T &operator[](u64 index) { return this->data[index]; }
};

};  // namespace ivy

#endif  // IVY_LIST_HPP_

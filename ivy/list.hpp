/*
 *  ----- Ivy List -----
 *  Version: 0.3.0
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

  ivy_forceinline static list make(allocator alloc, u64 capacity) {
    const u64 aligned = align_bytes(capacity);

    return (list){
        .data = (T *)alloc.alloc(aligned * sizeof(T)),
        .length = 0,
        .capacity = aligned,
        .alloc = alloc,
    };
  }

  T operator[](u64 index) { return this->data[index]; }
};

};  // namespace ivy

#endif  // IVY_LIST_HPP_

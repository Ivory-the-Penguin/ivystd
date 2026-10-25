/*
 *  ----- Ivy List -----
 *  Version: 0.9.3
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

  ivy_forceinline static list make(allocator &alloc) {
    return make(alloc, minimum_capacity);
  }

  inline static list make(allocator &alloc, u64 capacity) {
    const u64 aligned = align_bytes(capacity * sizeof(T));
    capacity = aligned / sizeof(T);

    return list{
        .data = (T *)alloc.alloc(aligned),
        .length = 0,
        .capacity = capacity,
        .alloc = alloc,
    };
  }

  inline void expand(u64 new_capacity) {
    const u64 aligned = align_bytes(new_capacity * sizeof(T));

    this->data = (T *)this->alloc.realloc(this->data, aligned);
    this->capacity = aligned / sizeof(T);
  }

  inline void push(const T &item) {
    if (this->length + 1 > this->capacity) {
      expand(this->capacity * 2);
    }

    memcpy(&this->data[this->length++], (void *)&item, sizeof(T));
  }

  ivy_forceinline void pop() { this->length--; }
  ivy_forceinline void clear() { this->length = 0; }

  inline void free() {
    this->alloc.free(this->data);
    this->length = 0;
    this->capacity = 0;
    this->alloc = {};
  }

  inline T &operator[](u64 index) { return this->data[index]; }

  inline T *begin() { return this->data; }
  inline T *end() { return this->data + this->length; }
};

};  // namespace ivy

#endif  // IVY_LIST_HPP_

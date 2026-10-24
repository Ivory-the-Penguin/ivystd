/*
 *  ----- Ivy String Builder -----
 *  Version: 0.2.0
 *  License: MIT-0
 */

#ifndef IVY_STRING_BUILDER_HPP_
#define IVY_STRING_BUILDER_HPP_

#include "allocator.hpp"
#include "core.hpp"

namespace ivy {

struct string_builder {
  u8 *data;
  u64 length;
  u64 capacity;
  allocator alloc;

  static constexpr u64 minimum_capacity = 8;

  static string_builder make(allocator alloc) {
    return (string_builder){
        .data = (u8 *)alloc.alloc(minimum_capacity * sizeof(u8)),
        .length = 0,
        .capacity = minimum_capacity,
        .alloc = alloc,
    };
  }

  void free() {
    this->alloc.free(this->data);
    this->data = nullptr;
    this->length = 0;
    this->capacity = 0;
  }
};

}  // namespace ivy

#endif  // IVY_STRING_BUILDER_HPP_

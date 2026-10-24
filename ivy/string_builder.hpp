/*
 *  ----- Ivy String Builder -----
 *  Version: 1.0.1
 *  License: MIT-0
 */

#ifndef IVY_STRING_BUILDER_HPP_
#define IVY_STRING_BUILDER_HPP_

#include "allocator.hpp"
#include "core.hpp"
#include "string_view.hpp"

namespace ivy {

struct string_builder {
  u8 *data;
  u64 length;
  u64 capacity;
  allocator alloc;

  static constexpr u64 minimum_capacity = 8;

  ivy_forceinline static string_builder make(allocator alloc, u64 capacity) {
    const u64 aligned = align_bytes(capacity * sizeof(u8));
    return (string_builder){
        .data = (u8 *)alloc.alloc(aligned * sizeof(u8)),
        .length = 0,
        .capacity = aligned,
        .alloc = alloc,
    };
  }

  ivy_forceinline static string_builder make(allocator alloc) {
    return make(alloc, minimum_capacity);
  }

  ivy_forceinline static string_builder make(allocator alloc, string_view sv) {
    string_builder out = make(alloc, sv.length);
    memcpy(out.data, sv.data, sv.length);
    return out;
  }

  void expand(u64 new_capacity) {
    const u64 aligned = align_bytes(new_capacity * sizeof(u8));

    this->data = (u8 *)this->alloc.realloc(this->data, aligned);
    this->capacity = aligned;
  }

  void append(u8 c) {
    if (this->length + 1 > this->capacity) {
      this->expand(this->capacity * 2);
    }

    this->data[this->length++] = c;
  }

  void append(string_view sv) {
    if (this->length + sv.length > this->capacity) {
      this->expand(this->length + sv.length);
    }

    memcpy(this->data + this->length, sv.data, sv.length);
    this->length += sv.length;
  }

  // use this very sparingly.
  // if you use this too often, that means this is the wrong tool for you
  ivy_forceinline void pop(u64 n) { this->length -= n; }

  string_view to_sv(allocator alloc) {
    u8 *buffer = (u8 *)alloc.alloc(this->length + 1);

    memcpy(buffer, this->data, this->length);
    buffer[this->length] = '\0';

    return (string_view){
        .data = buffer,
        .length = this->length,
    };
  }

  ivy_forceinline void free() {
    this->alloc.free(this->data);
    this->data = nullptr;
    this->length = 0;
    this->capacity = 0;
  }
};

}  // namespace ivy

#endif  // IVY_STRING_BUILDER_HPP_

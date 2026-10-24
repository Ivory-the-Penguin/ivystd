/*
 *  ----- Ivy String View -----
 *  Version: 0.6.0
 *  License: MIT-0
 */

#ifndef IVY_STRING_VIEW_HPP_
#define IVY_STRING_VIEW_HPP_

#include "allocator.hpp"
#include "core.hpp"

namespace ivy {

using is_type_fn = bool (*)(u8 c);

ivy_forceinline bool is_space(u8 c) {
  return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' ||
          c == '\r');
}

struct string_view {
  const u8 *data;
  u64 length;

  ivy_forceinline void chop_left(u64 n) {
    this->data += n;
    this->length -= n;
  }

  ivy_forceinline void chop_right(u64 n) { this->length -= n; }

  ivy_forceinline void trim_left() {
    while (this->length > 0 && is_space(this->data[0])) {
      this->chop_left(1);
    }
  }

  ivy_forceinline void trim_right() {
    while (this->length > 0 && is_space(this->data[this->length - 1])) {
      this->chop_right(1);
    }
  }

  ivy_forceinline void trim() {
    this->trim_left();
    this->trim_right();
  }

  inline string_view combine(allocator alloc, string_view b) {
    u8 *new_buffer = (u8 *)alloc.alloc(this->length + b.length + 1);

    memcpy(new_buffer, this->data, this->length);
    memcpy(new_buffer + this->length, b.data, b.length);

    new_buffer[this->length + b.length] = '\0';

    return (string_view){
        .data = new_buffer,
        .length = this->length + b.length,
    };
  }
};

ivy_forceinline string_view sv(const char *cstr) {
  return (string_view){
      .data = (const u8 *)cstr,
      .length = cstrlen(cstr),
  };
}

}  // namespace ivy

#endif  // IVY_STRING_VIEW_HPP_

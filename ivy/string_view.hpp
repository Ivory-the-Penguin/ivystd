/*
 *  ----- Ivy String View -----
 *  Version: 0.7.0
 *  License: MIT-0
 */

#ifndef IVY_STRING_VIEW_HPP_
#define IVY_STRING_VIEW_HPP_

#include "allocator.hpp"
#include "core.hpp"

namespace ivy {

using is_type_fn = bool (*)(u8 c);

ivy_forceinline bool is_lowercase(u8 c) { return c >= 'a' && c <= 'z'; }
ivy_forceinline bool is_uppercase(u8 c) { return c >= 'A' && c <= 'Z'; }
ivy_forceinline bool is_digit(u8 c) { return c >= '0' && c <= '9'; }
ivy_forceinline bool is_blank(u8 c) { return c == ' ' || c == '\t'; }
ivy_forceinline bool is_graphical(u8 c) { return c >= 33 && c <= 126; }

ivy_forceinline bool is_control(u8 c) {
  return (c >= 0 && c <= 31) || c == 127;
}

ivy_forceinline bool is_space(u8 c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' ||
         c == '\r';
}

ivy_forceinline bool is_punctuation(u8 c) {
  return (c >= 32 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) ||
         (c >= 123 && c <= 126);
}

ivy_forceinline bool is_printable(u8 c) {
  return is_graphical(c) || is_space(c);
}

ivy_forceinline bool is_letter(u8 c) {
  return is_lowercase(c) || is_uppercase(c);
}

ivy_forceinline bool is_letter_or_number(u8 c) {
  return is_letter(c) || is_digit(c);
}

ivy_forceinline bool is_hex_digit(u8 c) {
  return is_digit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
}

ivy_forceinline u8 to_lowercase(u8 c) { return (is_uppercase(c) ? c + 32 : c); }

ivy_forceinline u8 to_uppercase(u8 c) { return (is_lowercase(c) ? c - 32 : c); }

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

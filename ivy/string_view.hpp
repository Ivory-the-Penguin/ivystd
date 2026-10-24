/*
 *  ----- Ivy String View -----
 *  Version: 0.3.0
 *  License: MIT-0
 */

#ifndef IVY_STRING_VIEW_HPP_
#define IVY_STRING_VIEW_HPP_

#include "core.hpp"

namespace ivy {

struct string_view {
  const u8 *data;
  u64 length;

  ivy_forceinline void chop_left(u64 n) {
    this->data += n;
    this->length -= n;
  }

  ivy_forceinline void chop_right(u64 n) { this->length -= n; }
};

ivy_forceinline string_view sv(const char *cstr) {
  return (string_view){
      .data = (const u8 *)cstr,
      .length = cstrlen(cstr),
  };
}

}  // namespace ivy

#endif  // IVY_STRING_VIEW_HPP_

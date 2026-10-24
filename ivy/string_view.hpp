/*
 *  ----- Ivy String View -----
 *  Version: 0.2.0
 *  License: MIT-0
 */

#ifndef IVY_STRING_VIEW_HPP_
#define IVY_STRING_VIEW_HPP_

#include <string.h>

#include "core.hpp"

namespace ivy {

struct string_view {
  const u8 *data;
  u64 length;
};

ivy_forceinline string_view sv(const char *cstr) {
  return (string_view){
      .data = (const u8 *)cstr,
      .length = strlen(cstr),
  };
}

}  // namespace ivy

#endif  // IVY_STRING_VIEW_HPP_

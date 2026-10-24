/*
 *  ----- Ivy String View -----
 *  Version: 0.1.0
 *  License: MIT-0
 */

#ifndef IVY_STRING_VIEW_
#define IVY_STRING_VIEW_

#include "core.hpp"

namespace ivy {

struct string_view {
  const u8 *data;
  u64 length;
};

}  // namespace ivy

#endif  // IVY_STRING_VIEW_

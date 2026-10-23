/*
 * ----- Ivy Alloc -----
 *  Version: 0.1.0
 *  License: MIT-0
 */

#ifndef IVY_ALLOC_H_
#define IVY_ALLOC_H_

#include "core.hpp"

namespace ivy {

enum class alloc_flags : u8 {
  has_alloc = 1 << 0,
  has_realloc = 1 << 1,
  has_free = 1 << 2,
};

}

#endif  // IVY_ALLOC_H_

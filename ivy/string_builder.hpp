/*
 *  ----- Ivy String Builder -----
 *  Version: 0.1.0
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
};

}  // namespace ivy

#endif  // IVY_STRING_BUILDER_HPP_

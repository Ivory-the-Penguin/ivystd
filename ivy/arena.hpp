/*
 *  ----- Ivy Arena -----
 *  Version: 0.1.0
 *  License: MIT-0
 */

#ifndef IVY_ARENA_HPP_
#define IVY_ARENA_HPP_

#include "allocator.hpp"
#include "core.hpp"
#include "list.hpp"

namespace ivy {

struct arena {
  list<u8 *> chunks;
  list<void *> big_chunks;
  u64 offset;
  u64 current_chunk;
  allocator alloc;
};

}  // namespace ivy

#endif  // IVY_ARENA_HPP_

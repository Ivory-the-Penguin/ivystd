/*
 *  ----- Ivy Fixed Buffer -----
 *  Version: 0.3.0
 *  License: MIT-0
 */

#ifndef IVY_FIXED_BUFFER_HPP_
#define IVY_FIXED_BUFFER_HPP_

#include "core.hpp"

namespace ivy {

struct fixed_buffer {
  u8 *buffer;
  u64 offset;
  const u64 capacity;

  ivy_forceinline static fixed_buffer make(u8 *buffer, u64 n) {
    return (fixed_buffer){
        .buffer = buffer,
        .offset = 0,
        .capacity = n,
    };
  }

  ivy_forceinline void reset() { this->offset = 0; }

  ivy_forceinline void clear() {
    memset(this->buffer, 0, this->offset);
    this->reset();
  }
};

}  // namespace ivy

#endif  // IVY_FIXED_BUFFER_HPP_

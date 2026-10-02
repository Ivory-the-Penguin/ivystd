#ifndef IVY_MATH_H
#define IVY_MATH_H

#include "ivy_core.h"

static const float ivy_pi_f = 3.14159265359f;
static const double ivy_pi = 3.14159265358979323846;

IVY_FORCE_INLINE float ivy_rad2deg_f(float radians) {
  return radians * (180.0f / ivy_pi_f);
}
IVY_FORCE_INLINE float ivy_deg2rad_f(float degrees) {
  return degrees * (ivy_pi_f / 180.0f);
}
IVY_FORCE_INLINE double ivy_rad2deg_d(double radians) {
  return radians * (180.0 / ivy_pi);
}
IVY_FORCE_INLINE float ivy_deg2rad_d(double degrees) {
  return degrees * (ivy_pi / 180.0);
}

#define DEFINE_MATH_FUNCTION(type, typename)                                   \
  IVY_FORCE_INLINE type ivy_min_##typename(type a, type b) {                   \
    return (a < b ? a : b);                                                    \
  }                                                                            \
                                                                               \
  IVY_FORCE_INLINE type ivy_max_##typename(type a, type b) {                   \
    return (a > b ? a : b);                                                    \
  }

DEFINE_MATH_FUNCTION(float, f)
DEFINE_MATH_FUNCTION(double, d)
DEFINE_MATH_FUNCTION(int32_t, i32)
DEFINE_MATH_FUNCTION(int64_t, i64)
DEFINE_MATH_FUNCTION(uint32_t, u32)
DEFINE_MATH_FUNCTION(uint64_t, u64)

#define ivy_min(a, b)                                                          \
  _Generic((a),                                                                \
      float: ivy_min_f,                                                        \
      double: ivy_min_d,                                                       \
      int32_t: ivy_min_i32,                                                    \
      int64_t: ivy_min_i64,                                                    \
      uint32_t: ivy_min_u32,                                                   \
      uint64_t: ivy_min_u64)(a, b)

#define ivy_max(a, b)                                                          \
  _Generic((a),                                                                \
      float: ivy_max_f,                                                        \
      double: ivy_max_d,                                                       \
      int32_t: ivy_max_i32,                                                    \
      int64_t: ivy_max_i64,                                                    \
      uint32_t: ivy_max_u32,                                                   \
      uint64_t: ivy_max_u64)(a, b)

#endif
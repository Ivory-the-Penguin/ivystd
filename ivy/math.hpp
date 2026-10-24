/*
 *  ----- Ivy Math -----
 *  Version: 0.6.1
 *  License: MIT-0
 */

#ifndef IVY_MATH_HPP_
#define IVY_MATH_HPP_

#include "core.hpp"

namespace ivy {

constexpr f32 pi = 3.14159265359f;
constexpr f32 two_pi = pi * 2;
constexpr f32 half_pi = pi / 2;
constexpr f32 inv_pi = 1 / pi;
constexpr f32 inv_two_pi = 1 / two_pi;

template <typename T>
ivy_forceinline T rad2deg(T radians) {
  return (radians) * (180.0f / pi);
}

template <typename T>
ivy_forceinline T deg2rad(T degrees) {
  return (degrees) * (pi / 180.0f);
}

template <typename T>
ivy_forceinline T max(T a, T b) {
  return (a > b ? a : b);
}

template <typename T>
ivy_forceinline T min(T a, T b) {
  return (a < b ? a : b);
}

template <typename T>
ivy_forceinline T clamp(T value, T mn, T mx) {
  return max(min(value, mx), mn);
}

template <typename T>
ivy_forceinline T lerp(T a, T b, T t) {
  return (a * (1 - t) + b * t);
}

template <typename T>
ivy_forceinline T abs(T x) {
  return (x < 0 ? -x : x);
}

inline f32 pow(f32 x, i64 n) {
  if (n < 0) {
    x = 1 / x;
    n *= -1;
  }

  if (n == 0) {
    return 1;
  }

  f32 y = 1;
  while (n > 1) {
    if (n & 1) {
      y = x * y;
      n -= 1;
    }
    x = x * x;
    n >>= 1;
  }

  return x * y;
}

inline u64 pow(u64 x, u64 n) {
  if (n == 0) {
    return 1;
  }

  u64 y = 1;
  while (n > 1) {
    if (n & 1) {
      y = x * y;
      n -= 1;
    }
    x = x * x;
    n >>= 1;
  }

  return x * y;
}

ivy_forceinline i64 pow(i64 x, u64 n) {
  if (n == 0) {
    return 1;
  }

  i64 out = (i64)pow((x < 0 ? (u64)-x : (u64)x), n);

  return (x < 0 && (n & 1) ? -out : out);
}

ivy_forceinline bool compare_decimal(f32 a, f32 b, f32 precision) {
  return abs(a - b) <= precision;
}

inline f32 sin(f32 x) {
  f32 quot = x * inv_two_pi;
  f32 rounded = (f32)((int)(quot + (quot >= 0.0f ? 0.5f : -0.5f)));
  x -= two_pi * rounded;

  if (x > half_pi) {
    x = pi - x;
  }
  if (x < -half_pi) {
    x = -pi - x;
  }

  const f32 x2 = x * x;

  const f32 c1 = -1.666666667e-01f;
  const f32 c2 = 8.333333333e-03f;
  const f32 c3 = -1.984126984e-04f;
  const f32 c4 = 2.755731922e-06f;

  return x * (1.0f + x2 * (c1 + x2 * (c2 + x2 * (c3 + x2 * c4))));
}

ivy_forceinline f32 cos(f32 x) { return sin(x + half_pi); }
ivy_forceinline f32 tan(f32 x) { return sin(x) / cos(x); }

inline f32 inv_sqrt(f32 x) {
  i32 i;
  f32 x2, y;
  const f32 threehalfs = 1.5f;

  x2 = x * 0.5f;
  y = x;
  memcpy(&i, &y, sizeof(i));
  i = 0x5f3759df - (i >> 1);
  memcpy(&y, &i, sizeof(y));

  y = y * (threehalfs - (x2 * y * y));
  y = y * (threehalfs - (x2 * y * y));
  y = y * (threehalfs - (x2 * y * y));
  return y;
}

ivy_forceinline f32 sqrt(f32 x) { return (x > 0.0f ? x * inv_sqrt(x) : 0.0f); }

}  // namespace ivy

#endif  // IVY_MATH_HPP_

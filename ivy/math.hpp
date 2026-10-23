/*
 *  ----- Ivy Math -----
 *  Version: 0.3.0
 *  License: MIT-0
 */

#ifndef IVY_MATH_H_
#define IVY_MATH_H_

#include "core.hpp"

namespace ivy {

constexpr f32 pi = 3.14159265359f;
constexpr f32 two_pi = pi * 2;
constexpr f32 half_pi = pi / 2;
constexpr f32 inv_pi = 1 / pi;

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

inline i64 pow(i64 x, u64 n) {
  if (n == 0) {
    return 1;
  }

  i64 out = (i64)pow((x < 0 ? (u64)-x : (u64)x), n);

  if (x < 0 && (n & 1)) {
    out *= -1;
  }

  return out;
}

ivy_forceinline bool compare_decimal(f32 a, f32 b, f32 precision) {
  return abs(a - b) <= precision;
}

ivy_forceinline bool compare_decimal(f64 a, f64 b, f64 precision) {
  return abs(a - b) <= precision;
}

}  // namespace ivy

#endif  // IVY_MATH_H_

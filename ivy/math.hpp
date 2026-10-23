/*
 *  ----- Ivy Math -----
 *  Version: 0.1.0
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

}  // namespace ivy

#endif  // IVY_MATH_H_

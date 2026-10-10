/*
  ----- Ivy Math -----
  Version: 0.4.0
  License: MIT-0

  This header only library has some useful maths functions for the ivystd.
*/

#ifndef IVY_MATH_H
#define IVY_MATH_H

#define IVY_MATH_MAJOR 0
#define IVY_MATH_MINOR 4
#define IVY_MATH_FIX 0

#include "ivy_core.h"

#define IVY_PI 3.14159265359f
#define IVY_2PI 6.28318530718f
#define IVY_HALF_PI 1.570796326795f
#define IVY_INV_2PI 0.15915494309189533576f

#define IVY_RAD2DEG(radians) ((radians) * (180.0f / IVY_PI))
#define IVY_DEG2RAD(degrees) ((degrees) * (IVY_PI / 180.0f))

#define IVY_MIN(a, b) ((a) < (b) ? (a) : (b))
#define IVY_MAX(a, b) ((a) > (b) ? (a) : (b))

#define IVY_CLAMP(value, min, max) \
  ((value) > (max) ? (max) : ((value) < (min) ? (min) : (value)))

#define IVY_LERP(a, b, t) ((a) + ((b) - (a)) * (t))

#define IVY_ABS(x) ((x) < 0 ? -(x) : (x))

IVY_FORCE_INLINE float ivy_sin(float x) {
  float quot = x * IVY_INV_2PI;
  float rounded = (float)((int)(quot + (quot >= 0.0f ? 0.5f : -0.5f)));
  x = x - IVY_2PI * rounded;

  if (x > IVY_HALF_PI) x = IVY_PI - x;
  if (x < -IVY_HALF_PI) x = -IVY_PI - x;

  float x2 = x * x;

  const float c1 = -1.666666667e-01f;
  const float c2 = 8.333333333e-03f;
  const float c3 = -1.984126984e-04f;
  const float c4 = 2.755731922e-06f;

  return x * (1.0f + x2 * (c1 + x2 * (c2 + x2 * (c3 + x2 * c4))));
}

IVY_FORCE_INLINE float ivy_cos(float x) { return ivy_sin(x + IVY_HALF_PI); }

IVY_FORCE_INLINE float ivy_tan(float x) { return ivy_sin(x) / ivy_cos(x); }

IVY_FORCE_INLINE float ivy_inv_sqrt(float x) {
  long i;
  float x2, y;
  const float threehalfs = 1.5f;

  x2 = x * 0.5f;
  y = x;
  memcpy(&i, &y, sizeof(i));
  i = 0x5f3759df - (i >> 1);
  memcpy(&y, &i, sizeof(y));
  y = y * (threehalfs - (x2 * y * y));

  return y;
}

IVY_FORCE_INLINE float ivy_sqrt(float x) {
  return x > 0.0f ? x * ivy_inv_sqrt(x) : 0.0f;
}

IVY_FORCE_INLINE float ivy_pow(float x, int exp) {
  if (x == 0.0f && exp < 0) {
    return 0.0f;
  }

  float out = 1.0f;
  if (exp < 0) {
    x = 1.0f / x;
    exp = -exp;
  }

  for (int i = 0; i < exp; i++) {
    out *= x;
  }

  return out;
}

#endif

/*
  ----- Ivy Math -----
  Version: 0.1.0
  License: MIT-0

  This header only library has some useful maths functions for the ivystd.
*/

#ifndef IVY_MATH_H
#define IVY_MATH_H

#define IVY_MATH_MAJOR 0
#define IVY_MATH_MINOR 1
#define IVY_MATH_FIX 0

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

#endif
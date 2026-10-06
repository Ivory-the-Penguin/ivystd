/*
  ----- Ivy Color -----
  Version: 0.1.0
  License: MIT-0

  This is a header only library which has an implemention for colors
*/

#ifndef IVY_COLOR_H
#define IVY_COLOR_H

#define IVY_COLOR_MAJOR 0
#define IVY_COLOR_MINOR 1
#define IVY_COLOR_FIX 0

#include "ivy_core.h"
#include "ivy_linmath.h"

typedef vec4_t color_t;

#define COLOR_WHITE color(1.0f, 1.0f, 1.0f, 1.0f)
#define COLOR_RED color(1.0f, 0.0f, 0.0f, 1.0f)
#define COLOR_GREEN color(0.0f, 1.0f, 0.0f, 1.0f)
#define COLOR_BLUE color(0.0f, 0.0f, 1.0f, 1.0f)
#define COLOR_BLACK color(0.0f, 0.0f, 0.0f, 1.0f)
#define COLOR_NONE color(0.0f, 0.0f, 0.0f, 0.0f)

IVY_FORCE_INLINE color_t color(float r, float g, float b, float a) {
  return (color_t){
      .r = r,
      .g = g,
      .b = b,
      .a = a,
  };
}

IVY_FORCE_INLINE color_t color_lerp(color_t a, color_t b, float t) {
  return vec4_lerp(a, b, t);
}

#endif

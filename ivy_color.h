/*
  ----- Ivy Color -----
  Version: 0.2.1
  License: MIT-0

  This is a header only library which has an implemention for colors
*/

#ifndef IVY_COLOR_H
#define IVY_COLOR_H

#define IVY_COLOR_MAJOR 0
#define IVY_COLOR_MINOR 2
#define IVY_COLOR_FIX 1

#include "ivy_core.h"
#include "ivy_linmath.h"

typedef vec4_t color_t;

typedef union {
  struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
  };
  u32 packed;
} color_bytes_t;

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

IVY_FORCE_INLINE color_bytes_t color_to_cb(color_t c) {
  color_bytes_t cb;
  cb.r = (u8)(c.r < 0.0f ? 0 : (c.r > 1.0f ? 255 : (u8)(c.r * 255.0f)));
  cb.g = (u8)(c.g < 0.0f ? 0 : (c.g > 1.0f ? 255 : (u8)(c.g * 255.0f)));
  cb.b = (u8)(c.b < 0.0f ? 0 : (c.b > 1.0f ? 255 : (u8)(c.b * 255.0f)));
  cb.a = (u8)(c.a < 0.0f ? 0 : (c.a > 1.0f ? 255 : (u8)(c.a * 255.0f)));
  return cb;
}

IVY_FORCE_INLINE color_bytes_t cb_make(u8 r, u8 g, u8 b, u8 a) {
  return (color_bytes_t){
      .r = r,
      .g = g,
      .b = b,
      .a = a,
  };
}

IVY_FORCE_INLINE color_t color_from_cb(color_bytes_t cb) {
  return color(cb.r / 255.0f, cb.g / 255.0f, cb.b / 255.0f, cb.a / 255.0f);
}

IVY_FORCE_INLINE color_t color_lerp(color_t a, color_t b, float t) {
  return vec4_lerp(a, b, t);
}

#endif

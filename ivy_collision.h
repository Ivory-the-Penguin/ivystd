/*
  ----- Ivy Collision -----
  Version: 0.1.0
  License: MIT-0

  This is a header only library that has AABB collisions.

  It's planned to get expanded with other types such as circles, rays, etc.
*/

#ifndef IVY_COLLISION_H
#define IVY_COLLISION_H

#define IVY_COLLISION_MAJOR 0
#define IVY_COLLISION_MINOR 1
#define IVY_COLLISION_FIX 0

#include "ivy_core.h"
#include "ivy_linmath.h"

typedef struct {
  vec2_t min;
  vec2_t max;
} aabb2_t;

typedef struct {
  vec3_t min;
  vec3_t max;
} aabb3_t;

IVY_FORCE_INLINE aabb2_t aabb2_make(vec2_t min, vec2_t max) {
  return (aabb2_t){
      .min = min,
      .max = max,
  };
}

IVY_FORCE_INLINE aabb3_t aabb3_make(vec3_t min, vec3_t max) {
  return (aabb3_t){
      .min = min,
      .max = max,
  };
}

#endif

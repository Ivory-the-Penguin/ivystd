/*
  ----- Ivy Linmath -----
  Version: Pre-1.0.0
  License: MIT-0

  This is a header only library for linear algebra in the ivystd.
  Inspired by the C/C++ header only library, Handmade Math.

  My philosophy for this header is at ./docs/linmath.md

  ----- Usage -----
  The header uses GLM standards, so radians for angles, column major matrices,
  and right handed. Use the ivy_rad2deg or ivy_deg2rad functions in ivy_math
  (or it's builtin if you define IVY_LINMATH_STANDALONE).

  For vectors, it follows a pattern for the functions (and for C11 they have a
  generic variation). Let's assume n is the size of the vector (going from 2 to
  4). We have the follow functions:

  ~ vecn(...) : Makes a vector, with all the components (...)

  ~ vecn_s(float scalar) : Makes a vector, where each component is the scalar

  ~ vecn_add(a, b) : Returns a + b

  ~ vecn_sub(a, b) : Returns a - b

  ~ vecn_mul(a, b) : Returns a * b

  ~ vecn_div(a, b) : Returns a / b

  ~ vecn_add_s(vec, scalar) : Returns vec + vecn_s(scalar)

  ~ vecn_sub_s(vec, scalar) : Returns vec : vecn_s(scalar)

  ~ vecn_mul_s(vec, scalar) : Returns vec * vecn_s(scalar)

  ~ vecn_div_s(vec, scalar) : Returns vec / vecn_s(scalar)

  ~ vecn_dot(a, b) : Returns the dot product of a and b

  ~ vecn_len_sq(vec) : Returns the length of the vector squared

  ~ vecn_len(vec) : Returns the length of the vector

  ~ vecn_eq(a, b) : Returns true if all components of a is equal to b, false
  otherwise

  ~ vecn_norm(vec) : Returns the normalized (length is 1) vector (if vec is a
  zero vector, it returns a zero vector)

  ~ vecn_lerp(a, b, t) : Returns the lerp of a and b, at t% progress (0% is a,
  100% is b, anything else is in between)

  ~ vecn_dist_sq(a, b) : Returns the distance between point A and B squared

  ~ vecn_dist(a, b) : Returns the distance between point A and B

  ~ vecn_refl(vec, norm) : Returns vector vec reflected on the normal norm

  All of these functions have a generic variation (for C11 and above), where
  you don't have to specify the n part, so adding two vectors would be
  vec_add(a, b), and it automatically infers the type of vector a and b.

  There ARE a few vector functions that are specific for certain types. Such as:

  ~ vec3_vec2(vec, z) : Returns a 3D vector that comes from a 2D vector and a z
  component

  ~ vec4_vec3(vec, w) : Returns a 4D vector that comes from a 3D vector and a w
  component

  ~ vec3_cross(a, b) : Finds the cross product of 2 vectors (vec3 vectors)

  For every vector type there is a zero and one vector constant.

  ----- Credits -----
  Handmade Math inspired this header, and some of the functions (specifically
  for mat4 and quaternions) were copied from Handmade Math.
*/

#ifndef IVY_LINMATH_H
#define IVY_LINMATH_H

#define IVY_LINMATH_MAJOR 1 /* PRE 1 */
#define IVY_LINMATH_MINOR 0
#define IVY_LINMATH_FIX 0

#include "ivy_core.h"
#include "ivy_math.h"

#ifndef IVY_LINMATH_NO_SIMD

#ifdef _MSC_VER

#if defined(_M_AMD64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 1)
#define IVY_LINMATH_USE_SSE
#endif

#else

#ifdef __SSE__
#define IVY_LINMATH_USE_SSE
#endif

#endif

#ifdef __ARM_NEON
#define IVY_LINMATH_USE_NEON
#endif

#endif

#ifdef IVY_LINMATH_USE_SSE
#include <xmmintrin.h>
#endif

#ifdef IVY_LINMATH_USE_NEON
#include <arm_neon.h>
#endif

typedef union {
  struct {
    float x;
    float y;
  };

  struct {
    float u;
    float v;
  };

  struct {
    float width;
    float height;
  };

  float elements[2];
} vec2_t;

typedef union {
  struct {
    float x;
    float y;
    float z;
  };

  struct {
    float u;
    float v;
    float w;
  };

  struct {
    float r;
    float g;
    float b;
  };

  struct {
    vec2_t xy;
    float _ignored0;
  };

  struct {
    float _ignored1;
    vec2_t yz;
  };

  struct {
    vec2_t uv;
    float _ignored2;
  };

  struct {
    float _ignored3;
    vec2_t vw;
  };

  float elements[3];
} vec3_t;

typedef union {
  struct {
    union {
      vec3_t xyz;
      struct {
        float x;
        float y;
        float z;
      };
    };
    float w;
  };

  struct {
    union {
      vec3_t rgb;
      struct {
        float r;
        float g;
        float b;
      };
    };
    float a;
  };

  struct {
    vec2_t xy;
    float _ignored0;
    float _ignored1;
  };

  struct {
    float _ignored2;
    vec2_t yz;
    float _ignored3;
  };

  struct {
    float _ignored4;
    float _ignored5;
    vec2_t zw;
  };

  float elements[4];

#ifdef IVY_LINMATH_USE_SSE
  __m128 sse;
#endif

#ifdef IVY_LINMATH_USE_NEON
  float32x4_t neon;
#endif
} vec4_t;

typedef union {
  float elements[2][2];
  vec2_t columns[2];
} mat2_t;

typedef union {
  float elements[3][3];
  vec3_t columns[3];
} mat3_t;

typedef union {
  float elements[4][4];
  vec4_t columns[4];
} mat4_t;

typedef union {
  struct {
    union {
      vec3_t xyz;
      struct {
        float x;
        float y;
        float z;
      };
    };
    float w;
  };

  float elements[4];

#ifdef IVY_LINMATH_USE_SSE
  __m128 sse;
#endif

#ifdef IVY_LINMATH_USE_NEON
  float32x4_t neon;
#endif
} quat_t;

/*
 *  vec2 implementation
 */
static const vec2_t vec2_zero = (vec2_t){0.0f, 0.0f};
static const vec2_t vec2_one = (vec2_t){1.0f, 1.0f};

IVY_FORCE_INLINE vec2_t vec2(float x, float y) {
  return (vec2_t){.x = x, .y = y};
}

IVY_FORCE_INLINE vec2_t vec2_s(float scalar) {
  return (vec2_t){.x = scalar, .y = scalar};
}

IVY_FORCE_INLINE vec2_t vec2_add(vec2_t a, vec2_t b) {
  return vec2(a.x + b.x, a.y + b.y);
}

IVY_FORCE_INLINE vec2_t vec2_sub(vec2_t a, vec2_t b) {
  return vec2(a.x - b.x, a.y - b.y);
}

IVY_FORCE_INLINE vec2_t vec2_mul(vec2_t a, vec2_t b) {
  return vec2(a.x * b.x, a.y * b.y);
}

IVY_FORCE_INLINE vec2_t vec2_div(vec2_t a, vec2_t b) {
  return vec2(a.x / b.x, a.y / b.y);
}

IVY_FORCE_INLINE vec2_t vec2_add_s(vec2_t vec, float scalar) {
  return vec2_add(vec, vec2_s(scalar));
}

IVY_FORCE_INLINE vec2_t vec2_sub_s(vec2_t vec, float scalar) {
  return vec2_sub(vec, vec2_s(scalar));
}

IVY_FORCE_INLINE vec2_t vec2_mul_s(vec2_t vec, float scalar) {
  return vec2_mul(vec, vec2_s(scalar));
}

IVY_FORCE_INLINE vec2_t vec2_div_s(vec2_t vec, float scalar) {
  return vec2_div(vec, vec2_s(scalar));
}

IVY_FORCE_INLINE float vec2_dot(vec2_t a, vec2_t b) {
  return a.x * b.x + a.y * b.y;
}

IVY_FORCE_INLINE float vec2_len_sq(vec2_t vec) { return vec2_dot(vec, vec); }
IVY_FORCE_INLINE float vec2_len(vec2_t vec) { return sqrtf(vec2_len_sq(vec)); }

IVY_FORCE_INLINE bool vec2_eq(vec2_t a, vec2_t b) {
  return (a.x == b.x && a.y == b.y);
}

IVY_FORCE_INLINE vec2_t vec2_norm(vec2_t vec) {
  if (vec2_eq(vec, vec2_zero)) {
    return vec2_zero;
  }

  return vec2_div_s(vec, vec2_len(vec));
}

IVY_FORCE_INLINE vec2_t vec2_lerp(vec2_t a, vec2_t b, float t) {
  return vec2_add(a, vec2_mul_s(vec2_sub(b, a), t));
}

IVY_FORCE_INLINE float vec2_dist_sq(vec2_t a, vec2_t b) {
  return vec2_len_sq(vec2_sub(a, b));
}

IVY_FORCE_INLINE float vec2_dist(vec2_t a, vec2_t b) {
  return vec2_len(vec2_sub(a, b));
}

IVY_FORCE_INLINE vec2_t vec2_refl(vec2_t vec, vec2_t norm) {
  return vec2_sub(vec, vec2_mul_s(norm, 2.0f * vec2_dot(vec, norm)));
}

/*
 *  vec3 implementation
 */
static const vec3_t vec3_zero = (vec3_t){0.0f, 0.0f, 0.0f};
static const vec3_t vec3_one = (vec3_t){1.0f, 1.0f, 1.0f};

IVY_FORCE_INLINE vec3_t vec3(float x, float y, float z) {
  return (vec3_t){.x = x, .y = y, .z = z};
}

IVY_FORCE_INLINE vec3_t vec3_vec2(vec2_t xy, float z) {
  return (vec3_t){.x = xy.x, .y = xy.y, .z = z};
}

IVY_FORCE_INLINE vec3_t vec3_s(float scalar) {
  return (vec3_t){.x = scalar, .y = scalar, .z = scalar};
}

IVY_FORCE_INLINE vec3_t vec3_add(vec3_t a, vec3_t b) {
  return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

IVY_FORCE_INLINE vec3_t vec3_sub(vec3_t a, vec3_t b) {
  return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

IVY_FORCE_INLINE vec3_t vec3_mul(vec3_t a, vec3_t b) {
  return vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

IVY_FORCE_INLINE vec3_t vec3_div(vec3_t a, vec3_t b) {
  return vec3(a.x / b.x, a.y / b.y, a.z / b.z);
}

IVY_FORCE_INLINE vec3_t vec3_add_s(vec3_t vec, float scalar) {
  return vec3_add(vec, vec3_s(scalar));
}

IVY_FORCE_INLINE vec3_t vec3_sub_s(vec3_t vec, float scalar) {
  return vec3_sub(vec, vec3_s(scalar));
}

IVY_FORCE_INLINE vec3_t vec3_mul_s(vec3_t vec, float scalar) {
  return vec3_mul(vec, vec3_s(scalar));
}

IVY_FORCE_INLINE vec3_t vec3_div_s(vec3_t vec, float scalar) {
  return vec3_div(vec, vec3_s(scalar));
}

IVY_FORCE_INLINE float vec3_dot(vec3_t a, vec3_t b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

IVY_FORCE_INLINE float vec3_len_sq(vec3_t vec) { return vec3_dot(vec, vec); }
IVY_FORCE_INLINE float vec3_len(vec3_t vec) { return sqrtf(vec3_len_sq(vec)); }

IVY_FORCE_INLINE bool vec3_eq(vec3_t a, vec3_t b) {
  return (a.x == b.x && a.y == b.y && a.z == b.z);
}

IVY_FORCE_INLINE vec3_t vec3_norm(vec3_t vec) {
  if (vec3_eq(vec, vec3_zero)) {
    return vec3_zero;
  }

  return vec3_div_s(vec, vec3_len(vec));
}

IVY_FORCE_INLINE vec3_t vec3_cross(vec3_t a, vec3_t b) {
  return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x);
}

IVY_FORCE_INLINE vec3_t vec3_lerp(vec3_t a, vec3_t b, float t) {
  return vec3_add(a, vec3_mul_s(vec3_sub(b, a), t));
}

IVY_FORCE_INLINE vec3_t vec3_refl(vec3_t vec, vec3_t norm) {
  return vec3_sub(vec, vec3_mul_s(norm, 2.0f * vec3_dot(vec, norm)));
}

IVY_FORCE_INLINE float vec3_dist_sq(vec3_t a, vec3_t b) {
  return vec3_len_sq(vec3_sub(a, b));
}

IVY_FORCE_INLINE float vec3_dist(vec3_t a, vec3_t b) {
  return vec3_len(vec3_sub(a, b));
}

/*
 *  vec4 implementation
 */

static const vec4_t vec4_zero = (vec4_t){0.0f, 0.0f, 0.0f, 0.0f};
static const vec4_t vec4_one = (vec4_t){1.0f, 1.0f, 1.0f, 1.0f};

IVY_FORCE_INLINE vec4_t vec4(float x, float y, float z, float w) {
#ifdef IVY_LINMATH_USE_SSE
  return (vec4_t){.sse = _mm_setr_ps(x, y, z, w)};
#elif IVY_LINMATH_USE_NEON
  return (vec4_t){.neon = (float32x4_t){x, y, z, w}};
#else
  return (vec4_t){.x = x, .y = y, .z = z, .w = w};
#endif
}

IVY_FORCE_INLINE vec4_t vec4_vec3(vec3_t xyz, float w) {
  return vec4(xyz.x, xyz.y, xyz.z, w);
}

IVY_FORCE_INLINE vec4_t vec4_s(float scalar) {
#ifdef IVY_LINMATH_USE_SSE
  return (vec4_t){.sse = _mm_set1_ps(scalar)};
#elif IVY_LINMATH_USE_NEON
  return (vec4_t){.neon = vdupq_n_f32(scalar)};
#else
  return vec4(scalar, scalar, scalar, scalar);
#endif
}

IVY_FORCE_INLINE vec4_t vec4_add(vec4_t a, vec4_t b) {
#ifdef IVY_LINMATH_USE_SSE
  return (vec4_t){.sse = _mm_add_ps(a.sse, b.sse)};
#elif IVY_LINMATH_USE_NEON
  return (vec4_t){.neon = vaddq_f32(a.neon, b.neon)};
#else
  return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
#endif
}

IVY_FORCE_INLINE vec4_t vec4_sub(vec4_t a, vec4_t b) {
#ifdef IVY_LINMATH_USE_SSE
  return (vec4_t){.sse = _mm_sub_ps(a.sse, b.sse)};
#elif IVY_LINMATH_USE_NEON
  return (vec4_t){.neon = vsubq_f32(a.neon, b.neon)};
#else
  return vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
#endif
}

IVY_FORCE_INLINE vec4_t vec4_mul(vec4_t a, vec4_t b) {
#ifdef IVY_LINMATH_USE_SSE
  return (vec4_t){.sse = _mm_mul_ps(a.sse, b.sse)};
#elif IVY_LINMATH_USE_NEON
  return (vec4_t){.neon = vmulq_f32(a.neon, b.neon)};
#else
  return vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
#endif
}

IVY_FORCE_INLINE vec4_t vec4_div(vec4_t a, vec4_t b) {
#ifdef IVY_LINMATH_USE_SSE
  return (vec4_t){.sse = _mm_div_ps(a.sse, b.sse)};
#elif IVY_LINMATH_USE_NEON
  return (vec4_t){.neon = vdivq_f32(a.neon, b.neon)};
#else
  return vec4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
#endif
}

IVY_FORCE_INLINE vec4_t vec4_add_s(vec4_t vec, float scalar) {
  return vec4_add(vec, vec4_s(scalar));
}

IVY_FORCE_INLINE vec4_t vec4_sub_s(vec4_t vec, float scalar) {
  return vec4_sub(vec, vec4_s(scalar));
}

IVY_FORCE_INLINE vec4_t vec4_mul_s(vec4_t vec, float scalar) {
  return vec4_mul(vec, vec4_s(scalar));
}

IVY_FORCE_INLINE vec4_t vec4_div_s(vec4_t vec, float scalar) {
  return vec4_div(vec, vec4_s(scalar));
}

IVY_FORCE_INLINE float vec4_dot(vec4_t a, vec4_t b) {
#ifdef IVY_LINMATH_USE_SSE
  float out;

  __m128 sse_out1 = _mm_mul_ps(a.sse, b.sse);
  __m128 sse_out2 = _mm_shuffle_ps(sse_out1, sse_out1, _MM_SHUFFLE(2, 3, 0, 1));
  sse_out1 = _mm_add_ps(sse_out1, sse_out2);
  sse_out2 = _mm_shuffle_ps(sse_out1, sse_out1, _MM_SHUFFLE(0, 1, 2, 3));
  sse_out1 = _mm_add_ps(sse_out1, sse_out2);
  _mm_store_ss(&out, sse_out1);

  return out;
#elif IVY_LINMATH_USE_NEON
  float out;

  float32x4_t neon_mul_out = vmulq_f32(a.neon, b.neon);
  float32x4_t neon_half_add = vpaddq_f32(neon_mul_out, neon_mul_out);
  float32x4_t neon_full_add = vpaddq_f32(neon_half_add, neon_half_add);
  out = vgetq_lane_f32(neon_full_add, 0);

  return out;
#else
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
#endif
}

IVY_FORCE_INLINE float vec4_len_sq(vec4_t vec) { return vec4_dot(vec, vec); }
IVY_FORCE_INLINE float vec4_len(vec4_t vec) { return sqrtf(vec4_len_sq(vec)); }

IVY_FORCE_INLINE bool vec4_eq(vec4_t a, vec4_t b) {
  return (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
}

IVY_FORCE_INLINE vec4_t vec4_norm(vec4_t vec) {
  if (vec4_eq(vec, vec4_zero)) {
    return vec4_zero;
  }

  return vec4_div_s(vec, vec4_len(vec));
}

IVY_FORCE_INLINE vec4_t vec4_lerp(vec4_t a, vec4_t b, float t) {
  return vec4_add(a, vec4_mul_s(vec4_sub(b, a), t));
}

IVY_FORCE_INLINE float vec4_dist_sq(vec4_t a, vec4_t b) {
  return vec4_len_sq(vec4_sub(a, b));
}

IVY_FORCE_INLINE float vec4_dist(vec4_t a, vec4_t b) {
  return vec4_len(vec4_sub(a, b));
}

IVY_FORCE_INLINE vec4_t vec4_refl(vec4_t vec, vec4_t norm) {
  return vec4_sub(vec, vec4_mul_s(norm, 2.0f * vec4_dot(vec, norm)));
}

/*
 *  mat2 implementation
 */
IVY_FORCE_INLINE mat2_t mat2(float diagonal) {
  mat2_t out;

  out.columns[0] = vec2(diagonal, 0.0f);
  out.columns[1] = vec2(0.0f, diagonal);

  return out;
}

IVY_FORCE_INLINE mat2_t mat2_transpose(mat2_t mat) {
  mat2_t out = mat;

  out.elements[0][1] = mat.elements[1][0];
  out.elements[1][0] = mat.elements[0][1];

  return out;
}

IVY_FORCE_INLINE mat2_t mat2_add(mat2_t a, mat2_t b) {
  mat2_t out = mat2(0.0f);

  out.columns[0] = vec2_add(a.columns[0], b.columns[0]);
  out.columns[1] = vec2_add(a.columns[1], b.columns[1]);

  return out;
}

IVY_FORCE_INLINE mat2_t mat2_sub(mat2_t a, mat2_t b) {
  mat2_t out = mat2(0.0f);

  out.columns[0] = vec2_sub(a.columns[0], b.columns[0]);
  out.columns[1] = vec2_sub(a.columns[1], b.columns[1]);

  return out;
}

IVY_FORCE_INLINE vec2_t mat2_mul_vec2(mat2_t mat, vec2_t vec) {
  return vec2(mat.columns[0].x * vec.x + mat.columns[1].x * vec.y,
              mat.columns[0].y * vec.x + mat.columns[1].y * vec.y);
}

IVY_FORCE_INLINE mat2_t mat2_mul(mat2_t a, mat2_t b) {
  mat2_t out = mat2(1.0f);

  out.columns[0] = mat2_mul_vec2(a, b.columns[0]);
  out.columns[1] = mat2_mul_vec2(a, b.columns[1]);

  return out;
}

IVY_FORCE_INLINE mat2_t mat2_mul_s(mat2_t mat, float scalar) {
  mat2_t out = mat2(1.0f);

  out.columns[0] = vec2_mul_s(mat.columns[0], scalar);
  out.columns[1] = vec2_mul_s(mat.columns[1], scalar);

  return out;
}

IVY_FORCE_INLINE mat2_t mat2_div_s(mat2_t mat, float scalar) {
  mat2_t out = mat2(1.0f);

  out.columns[0] = vec2_div_s(mat.columns[0], scalar);
  out.columns[1] = vec2_div_s(mat.columns[1], scalar);

  return out;
}

IVY_FORCE_INLINE float mat2_det(mat2_t mat) {
  return mat.elements[0][0] * mat.elements[1][1] -
         mat.elements[0][1] * mat.elements[1][0];
}

IVY_FORCE_INLINE mat2_t mat2_inv(mat2_t mat) {
  mat2_t out;

  float inv_det = 1.0f / mat2_det(mat);
  out.elements[0][0] = inv_det * +mat.elements[1][1];
  out.elements[1][1] = inv_det * +mat.elements[0][0];
  out.elements[0][1] = inv_det * -mat.elements[0][1];
  out.elements[1][0] = inv_det * -mat.elements[1][0];

  return out;
}

/*
 *  mat3 implementation
 */
IVY_FORCE_INLINE mat3_t mat3(float diagonal) {
  mat3_t out;

  out.columns[0] = vec3(diagonal, 0.0f, 0.0f);
  out.columns[1] = vec3(0.0f, diagonal, 0.0f);
  out.columns[2] = vec3(0.0f, 0.0f, diagonal);

  return out;
}

IVY_FORCE_INLINE mat3_t mat3_transpose(mat3_t mat) {
  mat3_t out = mat;

  out.elements[0][1] = mat.elements[1][0];
  out.elements[0][2] = mat.elements[2][0];
  out.elements[1][0] = mat.elements[0][1];
  out.elements[1][2] = mat.elements[2][1];
  out.elements[2][1] = mat.elements[1][2];
  out.elements[2][0] = mat.elements[0][2];

  return out;
}

IVY_FORCE_INLINE mat3_t mat3_add(mat3_t a, mat3_t b) {
  mat3_t out = mat3(0.0f);

  out.columns[0] = vec3_add(a.columns[0], b.columns[0]);
  out.columns[1] = vec3_add(a.columns[1], b.columns[1]);
  out.columns[2] = vec3_add(a.columns[2], b.columns[2]);

  return out;
}

IVY_FORCE_INLINE mat3_t mat3_sub(mat3_t a, mat3_t b) {
  mat3_t out = mat3(0.0f);

  out.columns[0] = vec3_sub(a.columns[0], b.columns[0]);
  out.columns[1] = vec3_sub(a.columns[1], b.columns[1]);
  out.columns[2] = vec3_sub(a.columns[2], b.columns[2]);

  return out;
}

IVY_FORCE_INLINE vec3_t mat3_mul_vec3(mat3_t mat, vec3_t vec) {
  return vec3(mat.columns[0].x * vec.x + mat.columns[1].x * vec.y +
                  mat.columns[2].x * vec.z,
              mat.columns[0].y * vec.x + mat.columns[1].y * vec.y +
                  mat.columns[2].y * vec.z,
              mat.columns[0].z * vec.x + mat.columns[1].z * vec.y +
                  mat.columns[2].z * vec.z);
}

IVY_FORCE_INLINE mat3_t mat3_mul(mat3_t a, mat3_t b) {
  mat3_t out = mat3(1.0f);

  out.columns[0] = mat3_mul_vec3(a, b.columns[0]);
  out.columns[1] = mat3_mul_vec3(a, b.columns[1]);
  out.columns[2] = mat3_mul_vec3(a, b.columns[2]);

  return out;
}

IVY_FORCE_INLINE mat3_t mat3_mul_s(mat3_t mat, float scalar) {
  mat3_t out = mat3(1.0f);

  out.columns[0] = vec3_mul_s(mat.columns[0], scalar);
  out.columns[1] = vec3_mul_s(mat.columns[1], scalar);
  out.columns[2] = vec3_mul_s(mat.columns[2], scalar);

  return out;
}

IVY_FORCE_INLINE mat3_t mat3_div_s(mat3_t mat, float scalar) {
  mat3_t out = mat3(1.0f);

  out.columns[0] = vec3_div_s(mat.columns[0], scalar);
  out.columns[1] = vec3_div_s(mat.columns[1], scalar);
  out.columns[2] = vec3_div_s(mat.columns[2], scalar);

  return out;
}

IVY_FORCE_INLINE float mat3_det(mat3_t mat) {
  mat3_t cross;
  cross.columns[0] = vec3_cross(mat.columns[1], mat.columns[2]);
  cross.columns[1] = vec3_cross(mat.columns[2], mat.columns[0]);
  cross.columns[2] = vec3_cross(mat.columns[0], mat.columns[1]);

  return vec3_dot(cross.columns[2], mat.columns[2]);
}

IVY_FORCE_INLINE mat3_t mat3_inv(mat3_t mat) {
  mat3_t cross;
  cross.columns[0] = vec3_cross(mat.columns[1], mat.columns[2]);
  cross.columns[1] = vec3_cross(mat.columns[2], mat.columns[0]);
  cross.columns[2] = vec3_cross(mat.columns[0], mat.columns[1]);

  float inv_det = 1.0f / vec3_dot(cross.columns[2], mat.columns[2]);

  mat3_t out;
  out.columns[0] = vec3_mul_s(cross.columns[0], inv_det);
  out.columns[1] = vec3_mul_s(cross.columns[1], inv_det);
  out.columns[2] = vec3_mul_s(cross.columns[2], inv_det);

  return mat3_transpose(out);
}

/*
 *  mat4 implementation
 */
IVY_FORCE_INLINE mat4_t mat4(float diagonal) {
  mat4_t out;

  out.columns[0] = vec4(diagonal, 0.0f, 0.0f, 0.0f);
  out.columns[1] = vec4(0.0f, diagonal, 0.0f, 0.0f);
  out.columns[2] = vec4(0.0f, 0.0f, diagonal, 0.0f);
  out.columns[3] = vec4(0.0f, 0.0f, 0.0f, diagonal);

  return out;
}

IVY_FORCE_INLINE mat4_t mat4_transpose(mat4_t mat) {
  mat4_t out;

#ifdef IVY_LINMATH_USE_SSE
  out = mat;
  _MM_TRANSPOSE4_PS(out.columns[0].sse, out.columns[1].sse, out.columns[2].sse,
                    out.columns[3].sse);
#elif defined(IVY_LINMATH_USE_NEON)
  float32x4x4_t transposed = vld4q_f32((float *)mat.columns);
  out.columns[0].neon = transposed.val[0];
  out.columns[1].neon = transposed.val[1];
  out.columns[2].neon = transposed.val[2];
  out.columns[3].neon = transposed.val[3];
#else
  out.elements[0][0] = mat.elements[0][0];
  out.elements[0][1] = mat.elements[1][0];
  out.elements[0][2] = mat.elements[2][0];
  out.elements[0][3] = mat.elements[3][0];
  out.elements[1][0] = mat.elements[0][1];
  out.elements[1][1] = mat.elements[1][1];
  out.elements[1][2] = mat.elements[2][1];
  out.elements[1][3] = mat.elements[3][1];
  out.elements[2][0] = mat.elements[0][2];
  out.elements[2][1] = mat.elements[1][2];
  out.elements[2][2] = mat.elements[2][2];
  out.elements[2][3] = mat.elements[3][2];
  out.elements[3][0] = mat.elements[0][3];
  out.elements[3][1] = mat.elements[1][3];
  out.elements[3][2] = mat.elements[2][3];
  out.elements[3][3] = mat.elements[3][3];
#endif

  return out;
}

IVY_FORCE_INLINE mat4_t mat4_add(mat4_t a, mat4_t b) {
  mat4_t out = mat4(0.0f);

  out.columns[0] = vec4_add(a.columns[0], b.columns[0]);
  out.columns[1] = vec4_add(a.columns[1], b.columns[1]);
  out.columns[2] = vec4_add(a.columns[2], b.columns[2]);
  out.columns[3] = vec4_add(a.columns[3], b.columns[3]);

  return out;
}

IVY_FORCE_INLINE mat4_t mat4_sub(mat4_t a, mat4_t b) {
  mat4_t out = mat4(0.0f);

  out.columns[0] = vec4_sub(a.columns[0], b.columns[0]);
  out.columns[1] = vec4_sub(a.columns[1], b.columns[1]);
  out.columns[2] = vec4_sub(a.columns[2], b.columns[2]);
  out.columns[3] = vec4_sub(a.columns[3], b.columns[3]);

  return out;
}

IVY_FORCE_INLINE vec4_t mat4_mul_vec4(mat4_t a, vec4_t b) {
  vec4_t out;
#ifdef IVY_LINMATH_USE_SSE
  out.sse = _mm_mul_ps(_mm_shuffle_ps(b.sse, b.sse, 0x00), a.columns[0].sse);
  out.sse = _mm_add_ps(out.sse, _mm_mul_ps(_mm_shuffle_ps(b.sse, b.sse, 0x55),
                                           a.columns[1].sse));
  out.sse = _mm_add_ps(out.sse, _mm_mul_ps(_mm_shuffle_ps(b.sse, b.sse, 0xaa),
                                           a.columns[2].sse));
  out.sse = _mm_add_ps(out.sse, _mm_mul_ps(_mm_shuffle_ps(b.sse, b.sse, 0xff),
                                           a.columns[3].sse));
#elif defined(IVY_LINMATH_USE_NEON)
  out.neon = vmulq_laneq_f32(a.columns[0].neon, b.neon, 0);
  out.neon = vfmaq_laneq_f32(out.neon, a.columns[1].neon, b.neon, 1);
  out.neon = vfmaq_laneq_f32(out.neon, a.columns[2].neon, b.neon, 2);
  out.neon = vfmaq_laneq_f32(out.neon, a.columns[3].neon, b.neon, 3);
#else
  out.x = b.x * a.columns[0].x;
  out.y = b.x * a.columns[0].y;
  out.z = b.x * a.columns[0].z;
  out.w = b.x * a.columns[0].w;

  out.x += b.y * a.columns[1].x;
  out.y += b.y * a.columns[1].y;
  out.z += b.y * a.columns[1].z;
  out.w += b.y * a.columns[1].w;

  out.x += b.z * a.columns[2].x;
  out.y += b.z * a.columns[2].y;
  out.z += b.z * a.columns[2].z;
  out.w += b.z * a.columns[2].w;

  out.x += b.w * a.columns[3].x;
  out.y += b.w * a.columns[3].y;
  out.z += b.w * a.columns[3].z;
  out.w += b.w * a.columns[3].w;
#endif
  return out;
}

IVY_FORCE_INLINE mat4_t mat4_mul(mat4_t a, mat4_t b) {
  mat4_t out = mat4(1.0f);

  out.columns[0] = mat4_mul_vec4(a, b.columns[0]);
  out.columns[1] = mat4_mul_vec4(a, b.columns[1]);
  out.columns[2] = mat4_mul_vec4(a, b.columns[2]);
  out.columns[3] = mat4_mul_vec4(a, b.columns[3]);

  return out;
}

IVY_FORCE_INLINE mat4_t mat4_mul_s(mat4_t mat, float scalar) {
  mat4_t out;

#ifdef IVY_LINMATH_USE_SSE
  __m128 scalar_sse = vec4_s(scalar).sse;
  out.columns[0].sse = _mm_mul_ps(mat.columns[0].sse, scalar_sse);
  out.columns[1].sse = _mm_mul_ps(mat.columns[1].sse, scalar_sse);
  out.columns[2].sse = _mm_mul_ps(mat.columns[2].sse, scalar_sse);
  out.columns[3].sse = _mm_mul_ps(mat.columns[3].sse, scalar_sse);
#else
  out.columns[0] = vec4_mul_s(mat.columns[0], scalar);
  out.columns[1] = vec4_mul_s(mat.columns[1], scalar);
  out.columns[2] = vec4_mul_s(mat.columns[2], scalar);
  out.columns[3] = vec4_mul_s(mat.columns[3], scalar);
#endif

  return out;
}

IVY_FORCE_INLINE mat4_t mat4_div_s(mat4_t mat, float scalar) {
  mat4_t out;
#ifdef IVY_LINMATH_USE_SSE
  __m128 scalar_sse = vec4_s(scalar).sse;
  out.columns[0].sse = _mm_div_ps(mat.columns[0].sse, scalar_sse);
  out.columns[1].sse = _mm_div_ps(mat.columns[1].sse, scalar_sse);
  out.columns[2].sse = _mm_div_ps(mat.columns[2].sse, scalar_sse);
  out.columns[3].sse = _mm_div_ps(mat.columns[3].sse, scalar_sse);
#else
  out.columns[0] = vec4_div_s(mat.columns[0], scalar);
  out.columns[1] = vec4_div_s(mat.columns[1], scalar);
  out.columns[2] = vec4_div_s(mat.columns[2], scalar);
  out.columns[3] = vec4_div_s(mat.columns[3], scalar);
#endif

  return out;
}

// some type of magic, copied from Handmade Math
IVY_FORCE_INLINE float mat4_det(mat4_t mat) {
  vec3_t c01 = vec3_cross(mat.columns[0].xyz, mat.columns[1].xyz);
  vec3_t c23 = vec3_cross(mat.columns[2].xyz, mat.columns[3].xyz);

  vec3_t b10 = vec3_sub(vec3_mul_s(mat.columns[0].xyz, mat.columns[1].w),
                        vec3_mul_s(mat.columns[1].xyz, mat.columns[0].w));
  vec3_t b32 = vec3_sub(vec3_mul_s(mat.columns[2].xyz, mat.columns[3].w),
                        vec3_mul_s(mat.columns[3].xyz, mat.columns[2].w));

  return vec3_dot(c01, b32) + vec3_dot(c23, b10);
}

IVY_FORCE_INLINE mat4_t mat4_inv(mat4_t mat) {
  vec3_t c01 = vec3_cross(mat.columns[0].xyz, mat.columns[1].xyz);
  vec3_t c23 = vec3_cross(mat.columns[2].xyz, mat.columns[3].xyz);
  vec3_t b10 = vec3_sub(vec3_mul_s(mat.columns[0].xyz, mat.columns[1].w),
                        vec3_mul_s(mat.columns[1].xyz, mat.columns[0].w));
  vec3_t b32 = vec3_sub(vec3_mul_s(mat.columns[2].xyz, mat.columns[3].w),
                        vec3_mul_s(mat.columns[3].xyz, mat.columns[2].w));

  float InvDeterminant = 1.0f / (vec3_dot(c01, b32) + vec3_dot(c23, b10));
  c01 = vec3_mul_s(c01, InvDeterminant);
  c23 = vec3_mul_s(c23, InvDeterminant);
  b10 = vec3_mul_s(b10, InvDeterminant);
  b32 = vec3_mul_s(b32, InvDeterminant);

  mat4_t out;
  out.columns[0] = vec4_vec3(vec3_add(vec3_cross(mat.columns[1].xyz, b32),
                                      vec3_mul_s(c23, mat.columns[1].w)),
                             -vec3_dot(mat.columns[1].xyz, c23));
  out.columns[1] = vec4_vec3(vec3_sub(vec3_cross(b32, mat.columns[0].xyz),
                                      vec3_mul_s(c23, mat.columns[0].w)),
                             +vec3_dot(mat.columns[0].xyz, c23));
  out.columns[2] = vec4_vec3(vec3_add(vec3_cross(mat.columns[3].xyz, b10),
                                      vec3_mul_s(c01, mat.columns[3].w)),
                             -vec3_dot(mat.columns[3].xyz, c01));
  out.columns[3] = vec4_vec3(vec3_sub(vec3_cross(b10, mat.columns[2].xyz),
                                      vec3_mul_s(c01, mat.columns[2].w)),
                             +vec3_dot(mat.columns[2].xyz, c01));

  return mat4_transpose(out);
}

IVY_FORCE_INLINE mat4_t mat4_translate(vec3_t translate) {
  mat4_t out = mat4(1.0f);
  out.columns[3] = vec4(translate.x, translate.y, translate.z, 1.0f);

  return out;
}

IVY_FORCE_INLINE mat4_t mat4_scale(vec3_t scale) {
  mat4_t out = mat4(1.0f);
  out.elements[0][0] = scale.x;
  out.elements[1][1] = scale.y;
  out.elements[2][2] = scale.z;

  return out;
}

IVY_FORCE_INLINE mat4_t mat4_rotate(float angle, vec3_t axis) {
  mat4_t out = mat4(1.0f);

  axis = vec3_norm(axis);

  float sin_theta = sinf(angle);
  float cos_theta = cosf(angle);
  float cos_value = 1.0f - cos_theta;

  out.elements[0][0] = (axis.x * axis.x * cos_value) + cos_theta;
  out.elements[1][1] = (axis.y * axis.y * cos_value) + cos_theta;
  out.elements[2][2] = (axis.z * axis.z * cos_value) + cos_theta;

  out.elements[0][1] = (axis.x * axis.y * cos_value) + (axis.z * sin_theta);
  out.elements[0][2] = (axis.x * axis.z * cos_value) - (axis.y * sin_theta);

  out.elements[1][0] = (axis.y * axis.x * cos_value) - (axis.z * sin_theta);
  out.elements[1][2] = (axis.y * axis.z * cos_value) + (axis.x * sin_theta);

  out.elements[2][0] = (axis.z * axis.x * cos_value) + (axis.y * sin_theta);
  out.elements[2][1] = (axis.z * axis.y * cos_value) - (axis.x * sin_theta);

  return out;
}

/*
 * Generic macros
 */
#ifdef IVY_ATLEAST_C11

#define vec_add(a, b) \
  _Generic((a), vec2_t: vec2_add, vec3_t: vec3_add, vec4_t: vec4_add)((a), (b))

#define vec_sub(a, b) \
  _Generic((a), vec2_t: vec2_sub, vec3_t: vec3_sub, vec4_t: vec4_sub)((a), (b))

#define vec_mul(a, b) \
  _Generic((a), vec2_t: vec2_mul, vec3_t: vec3_mul, vec4_t: vec4_mul)((a), (b))

#define vec_div(a, b) \
  _Generic((a), vec2_t: vec2_div, vec3_t: vec3_div, vec4_t: vec4_div)((a), (b))

#define vec_add_s(vec, scalar)                                                 \
  _Generic((vec), vec2_t: vec2_add_s, vec3_t: vec3_add_s, vec4_t: vec4_add_s)( \
      (vec), (scalar))

#define vec_sub_s(vec, scalar)                                                 \
  _Generic((vec), vec2_t: vec2_sub_s, vec3_t: vec3_sub_s, vec4_t: vec4_sub_s)( \
      (vec), (scalar))

#define vec_mul_s(vec, scalar)                                                 \
  _Generic((vec), vec2_t: vec2_mul_s, vec3_t: vec3_mul_s, vec4_t: vec4_mul_s)( \
      (vec), (scalar))

#define vec_div_s(vec, scalar)                                                 \
  _Generic((vec), vec2_t: vec2_div_s, vec3_t: vec3_div_s, vec4_t: vec4_div_s)( \
      (vec), (scalar))

#define vec_dot(a, b) \
  _Generic((a), vec2_t: vec2_dot, vec3_t: vec3_dot, vec4_t: vec4_dot)((a), (b))

#define vec_len_sq(vec)    \
  _Generic((vec),          \
      vec2_t: vec2_len_sq, \
      vec3_t: vec3_len_sq, \
      vec4_t: vec4_len_sq)((vec))

#define vec_len(vec) \
  _Generic((vec), vec2_t: vec2_len, vec3_t: vec3_len, vec4_t: vec4_len)((vec))

#define vec_eq(a, b) \
  _Generic((a), vec2_t: vec2_eq, vec3_t: vec3_eq, vec4_t: vec4_eq)((a), (b))

#define vec_norm(vec)                                                       \
  _Generic((vec), vec2_t: vec2_norm, vec3_t: vec3_norm, vec4_t: vec4_norm)( \
      (vec))

#define vec_lerp(a, b, t)                                                 \
  _Generic((a), vec2_t: vec2_lerp, vec3_t: vec3_lerp, vec4_t: vec4_lerp)( \
      (a), (b), (t))

#define vec_dist_sq(a, b)   \
  _Generic((a),             \
      vec2_t: vec2_dist_sq, \
      vec3_t: vec3_dist_sq, \
      vec4_t: vec4_dist_sq)((a), (b))

#define vec_dist(a, b)                                                        \
  _Generic((a), vec2_t: vec2_dist, vec3_t: vec3_dist, vec4_t: vec4_dist)((a), \
                                                                         (b))

#define vec_refl(vec, norm)                                                 \
  _Generic((vec), vec2_t: vec2_refl, vec3_t: vec3_refl, vec4_t: vec4_refl)( \
      (vec), (norm))

#define mat_transpose(mat)    \
  _Generic((mat),             \
      mat2_t: mat2_transpose, \
      mat3_t: mat3_transpose, \
      mat4_t: mat4_transpose)((mat))

#define mat_add(a, b) \
  _Generic((a), mat2_t: mat2_add, mat3_t: mat3_add, mat4_t: mat4_add)((a), (b))

#define mat_sub(a, b) \
  _Generic((a), mat2_t: mat2_sub, mat3_t: mat3_sub, mat4_t: mat4_sub)((a), (b))

#define mat_mul_vec(mat, vec) \
  _Generic((mat),             \
      mat2_t: mat2_mul_vec2,  \
      mat3_t: mat3_mul_vec3,  \
      mat4_t: mat4_mul_vec4)((mat), (vec))

#define mat_mul(a, b) \
  _Generic((a), mat2_t: mat2_mul, mat3_t: mat3_mul, mat4_t: mat4_mul)((a), (b))

#define mat_mul_s(a, b)                                                      \
  _Generic((a), mat2_t: mat2_mul_s, mat3_t: mat3_mul_s, mat4_t: mat4_mul_s)( \
      (a), (b))

#define mat_div_s(a, b)                                                      \
  _Generic((a), mat2_t: mat2_div_s, mat3_t: mat3_div_s, mat4_t: mat4_div_s)( \
      (a), (b))

#define mat_det(mat) \
  _Generic((mat), mat2_t: mat2_det, mat3_t: mat3_det, mat4_t: mat4_det)((mat))

#define mat_inv(mat) \
  _Generic((mat), mat2_t: mat2_inv, mat3_t: mat3_inv, mat4_t: mat4_inv)((mat))

#endif

#endif

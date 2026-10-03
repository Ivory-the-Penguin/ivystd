#ifndef IVY_LINMATH_H
#define IVY_LINMATH_H

#include "ivy_core.h"
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
} quat_t;

IVY_FORCE_INLINE vec2_t vec2(float x, float y) {
  return (vec2_t){.x = x, .y = y};
}

IVY_FORCE_INLINE vec3_t vec3(float x, float y, float z) {
  return (vec3_t){.x = x, .y = y, .z = z};
}

IVY_FORCE_INLINE vec4_t vec4(float x, float y, float z, float w) {
  return (vec4_t){.x = x, .y = y, .z = z, .w = w};
}

IVY_FORCE_INLINE vec2_t vec2_s(float scalar) {
  return (vec2_t){.x = scalar, .y = scalar};
}

IVY_FORCE_INLINE vec3_t vec3_s(float scalar) {
  return (vec3_t){.x = scalar, .y = scalar, .z = scalar};
}

IVY_FORCE_INLINE vec4_t vec4_s(float scalar) {
  return (vec4_t){.x = scalar, .y = scalar, .z = scalar, .w = scalar};
}

IVY_FORCE_INLINE mat2_t mat2(float scalar) {
  return (mat2_t){
      .elements =
          {
              {scalar, 0.0f},
              {0.0f, scalar},
          },
  };
}

IVY_FORCE_INLINE mat3_t mat3(float scalar) {
  return (mat3_t){
      .elements =
          {
              {scalar, 0.0f, 0.0f},
              {0.0f, scalar, 0.0f},
              {0.0f, 0.0f, scalar},
          },
  };
}

IVY_FORCE_INLINE mat4_t mat4(float scalar) {
  return (mat4_t){
      .elements =
          {
              {scalar, 0.0f, 0.0f, 0.0f},
              {0.0f, scalar, 0.0f, 0.0f},
              {0.0f, 0.0f, scalar, 0.0f},
              {0.0f, 0.0f, 0.0f, scalar},
          },
  };
}

IVY_FORCE_INLINE vec2_t vec2_add(vec2_t a, vec2_t b) {
  return vec2(a.x + b.x, a.y + b.y);
}

IVY_FORCE_INLINE vec3_t vec3_add(vec3_t a, vec3_t b) {
  return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

IVY_FORCE_INLINE vec4_t vec4_add(vec4_t a, vec4_t b) {
  return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

IVY_FORCE_INLINE vec2_t vec2_sub(vec2_t a, vec2_t b) {
  return vec2(a.x - b.x, a.y - b.y);
}

IVY_FORCE_INLINE vec3_t vec3_sub(vec3_t a, vec3_t b) {
  return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

IVY_FORCE_INLINE vec4_t vec4_sub(vec4_t a, vec4_t b) {
  return vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

IVY_FORCE_INLINE vec2_t vec2_mul(vec2_t a, vec2_t b) {
  return vec2(a.x * b.x, a.y * b.y);
}

IVY_FORCE_INLINE vec3_t vec3_mul(vec3_t a, vec3_t b) {
  return vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

IVY_FORCE_INLINE vec4_t vec4_mul(vec4_t a, vec4_t b) {
  return vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

IVY_FORCE_INLINE vec2_t vec2_div(vec2_t a, vec2_t b) {
  return vec2(a.x / b.x, a.y / b.y);
}

IVY_FORCE_INLINE vec3_t vec3_div(vec3_t a, vec3_t b) {
  return vec3(a.x / b.x, a.y / b.y, a.z / b.z);
}

IVY_FORCE_INLINE vec4_t vec4_div(vec4_t a, vec4_t b) {
  return vec4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

#define vec_add(a, b)                                                          \
  _Generic((a), vec2_t: vec2_add, vec3_t: vec3_add, vec4_t: vec4_add)(a, b)

#define vec_sub(a, b)                                                          \
  _Generic((a), vec2_t: vec2_sub, vec3_t: vec3_sub, vec4_t: vec4_sub)(a, b)

#define vec_mul(a, b)                                                          \
  _Generic((a), vec2_t: vec2_mul, vec3_t: vec3_mul, vec4_t: vec4_mul)(a, b)

#define vec_div(a, b)                                                          \
  _Generic((a), vec2_t: vec2_div, vec3_t: vec3_div, vec4_t: vec4_div)(a, b)

IVY_FORCE_INLINE vec2_t vec2_add_s(vec2_t vec, float scalar) {
  return vec2(vec.x + scalar, vec.y + scalar);
}

IVY_FORCE_INLINE vec3_t vec3_add_s(vec3_t vec, float scalar) {
  return vec3(vec.x + scalar, vec.y + scalar, vec.z + scalar);
}

IVY_FORCE_INLINE vec4_t vec4_add_s(vec4_t vec, float scalar) {
  return vec4(vec.x + scalar, vec.y + scalar, vec.z + scalar, vec.w + scalar);
}

IVY_FORCE_INLINE vec2_t vec2_sub_s(vec2_t vec, float scalar) {
  return vec2(vec.x - scalar, vec.y - scalar);
}

IVY_FORCE_INLINE vec3_t vec3_sub_s(vec3_t vec, float scalar) {
  return vec3(vec.x - scalar, vec.y - scalar, vec.z - scalar);
}

IVY_FORCE_INLINE vec4_t vec4_sub_s(vec4_t vec, float scalar) {
  return vec4(vec.x - scalar, vec.y - scalar, vec.z - scalar, vec.w - scalar);
}

IVY_FORCE_INLINE vec2_t vec2_mul_s(vec2_t vec, float scalar) {
  return vec2(vec.x * scalar, vec.y * scalar);
}

IVY_FORCE_INLINE vec3_t vec3_mul_s(vec3_t vec, float scalar) {
  return vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

IVY_FORCE_INLINE vec4_t vec4_mul_s(vec4_t vec, float scalar) {
  return vec4(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
}

IVY_FORCE_INLINE vec2_t vec2_div_s(vec2_t vec, float scalar) {
  return vec2(vec.x / scalar, vec.y / scalar);
}

IVY_FORCE_INLINE vec3_t vec3_div_s(vec3_t vec, float scalar) {
  return vec3(vec.x / scalar, vec.y / scalar, vec.z / scalar);
}

IVY_FORCE_INLINE vec4_t vec4_div_s(vec4_t vec, float scalar) {
  return vec4(vec.x / scalar, vec.y / scalar, vec.z / scalar, vec.w / scalar);
}

#define vec_add_s(vec, scalar)                                                 \
  _Generic((vec), vec2_t: vec2_add_s, vec3_t: vec3_add_s, vec4_t: vec4_add_s)( \
      vec, scalar)

#define vec_sub_s(vec, scalar)                                                 \
  _Generic((vec), vec2_t: vec2_sub_s, vec3_t: vec3_sub_s, vec4_t: vec4_sub_s)( \
      vec, scalar)

#define vec_mul_s(vec, scalar)                                                 \
  _Generic((vec), vec2_t: vec2_mul_s, vec3_t: vec3_mul_s, vec4_t: vec4_mul_s)( \
      vec, scalar)

#define vec_div_s(a, scalar)                                                   \
  _Generic((a), vec2_t: vec2_div_s, vec3_t: vec3_div_s, vec4_t: vec4_div_s)(   \
      vec, scalar)

IVY_FORCE_INLINE float vec2_dot(vec2_t a, vec2_t b) {
  return a.x * b.x + a.y * b.y;
}

IVY_FORCE_INLINE float vec3_dot(vec3_t a, vec3_t b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

IVY_FORCE_INLINE float vec4_dot(vec4_t a, vec4_t b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

#define vec_dot(a, b)                                                          \
  _Generic((a), vec2_t: vec2_dot, vec3_t: vec3_dot, vec4_t: vec4_dot)(a, b)

IVY_FORCE_INLINE float vec2_len_sq(vec2_t vec) { return vec2_dot(vec, vec); }
IVY_FORCE_INLINE float vec3_len_sq(vec3_t vec) { return vec3_dot(vec, vec); }
IVY_FORCE_INLINE float vec4_len_sq(vec4_t vec) { return vec4_dot(vec, vec); }

IVY_FORCE_INLINE float vec2_len(vec2_t vec) { return sqrtf(vec2_len_sq(vec)); }
IVY_FORCE_INLINE float vec3_len(vec3_t vec) { return sqrtf(vec3_len_sq(vec)); }
IVY_FORCE_INLINE float vec4_len(vec4_t vec) { return sqrtf(vec4_len_sq(vec)); }

#define vec_len_sq(vec)                                                        \
  _Generic((vec),                                                              \
      vec2_t: vec2_len_sq,                                                     \
      vec3_t: vec3_len_sq,                                                     \
      vec4_t: vec4_len_sq)(vec)

#define vec_len(vec)                                                           \
  _Generic((vec), vec2_t: vec2_len, vec3_t: vec3_len, vec4_t: vec4_len)(vec)

IVY_FORCE_INLINE vec2_t vec2_norm(vec2_t vec) {
  return vec2_div_s(vec, vec2_len(vec));
}

IVY_FORCE_INLINE vec3_t vec3_norm(vec3_t vec) {
  return vec3_div_s(vec, vec3_len(vec));
}

IVY_FORCE_INLINE vec4_t vec4_norm(vec4_t vec) {
  return vec4_div_s(vec, vec4_len(vec));
}

#define vec_norm(vec)                                                          \
  _Generic((vec), vec2_t: vec2_norm, vec3_t: vec3_norm, vec4_t: vec4_norm)(vec)

#ifdef IVY_IMPL

#endif

#endif
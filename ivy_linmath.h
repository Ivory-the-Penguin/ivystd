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

IVY_FORCE_INLINE float vec2_dot(vec2_t a, vec2_t b) {
  return a.x * b.x + a.y * b.y;
}

IVY_FORCE_INLINE float vec3_dot(vec3_t a, vec3_t b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

IVY_FORCE_INLINE float vec4_dot(vec4_t a, vec4_t b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

IVY_FORCE_INLINE float vec2_len_sq(vec2_t vec) { return vec2_dot(vec, vec); }
IVY_FORCE_INLINE float vec3_len_sq(vec3_t vec) { return vec3_dot(vec, vec); }
IVY_FORCE_INLINE float vec4_len_sq(vec4_t vec) { return vec4_dot(vec, vec); }

IVY_FORCE_INLINE float vec2_len(vec2_t vec) { return sqrtf(vec2_len_sq(vec)); }
IVY_FORCE_INLINE float vec3_len(vec3_t vec) { return sqrtf(vec3_len_sq(vec)); }
IVY_FORCE_INLINE float vec4_len(vec4_t vec) { return sqrtf(vec4_len_sq(vec)); }

IVY_FORCE_INLINE vec2_t vec2_norm(vec2_t vec) {
  return vec2_div_s(vec, vec2_len(vec));
}

IVY_FORCE_INLINE vec3_t vec3_norm(vec3_t vec) {
  return vec3_div_s(vec, vec3_len(vec));
}

IVY_FORCE_INLINE vec4_t vec4_norm(vec4_t vec) {
  return vec4_div_s(vec, vec4_len(vec));
}

IVY_FORCE_INLINE vec3_t vec3_cross(vec3_t a, vec3_t b) {
  return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x);
}

IVY_FORCE_INLINE vec2_t vec2_lerp(vec2_t a, vec2_t b, float t) {
  return vec2_add(a, vec2_mul_s(vec2_sub(b, a), t));
}

IVY_FORCE_INLINE vec3_t vec3_lerp(vec3_t a, vec3_t b, float t) {
  return vec3_add(a, vec3_mul_s(vec3_sub(b, a), t));
}

IVY_FORCE_INLINE vec4_t vec4_lerp(vec4_t a, vec4_t b, float t) {
  return vec4_add(a, vec4_mul_s(vec4_sub(b, a), t));
}

IVY_FORCE_INLINE float vec2_dist_sq(vec2_t a, vec2_t b) {
  return vec2_len_sq(vec2_sub(a, b));
}

IVY_FORCE_INLINE float vec3_dist_sq(vec3_t a, vec3_t b) {
  return vec3_len_sq(vec3_sub(a, b));
}

IVY_FORCE_INLINE float vec4_dist_sq(vec4_t a, vec4_t b) {
  return vec4_len_sq(vec4_sub(a, b));
}

IVY_FORCE_INLINE float vec2_dist(vec2_t a, vec2_t b) {
  return vec2_len(vec2_sub(a, b));
}

IVY_FORCE_INLINE float vec3_dist(vec3_t a, vec3_t b) {
  return vec3_len(vec3_sub(a, b));
}

IVY_FORCE_INLINE float vec4_dist(vec4_t a, vec4_t b) {
  return vec4_len(vec4_sub(a, b));
}

IVY_FORCE_INLINE vec2_t vec2_refl(vec2_t vec, vec2_t norm) {
  return vec2_sub(vec, vec2_mul_s(norm, 2.0f * vec2_dot(vec, norm)));
}

IVY_FORCE_INLINE vec3_t vec3_refl(vec3_t vec, vec3_t norm) {
  return vec3_sub(vec, vec3_mul_s(norm, 2.0f * vec3_dot(vec, norm)));
}

IVY_FORCE_INLINE vec4_t vec4_refl(vec4_t vec, vec4_t norm) {
  return vec4_sub(vec, vec4_mul_s(norm, 2.0f * vec4_dot(vec, norm)));
}

IVY_FORCE_INLINE vec2_t mat2_mul_vec2(mat2_t mat, vec2_t vec) {
  return vec2(mat.columns[0].x * vec.x + mat.columns[1].x * vec.y,
              mat.columns[0].y * vec.x + mat.columns[1].y * vec.y);
}

IVY_FORCE_INLINE vec3_t mat3_mul_vec3(mat3_t mat, vec3_t vec) {
  return vec3(mat.columns[0].x * vec.x + mat.columns[1].x * vec.y +
                  mat.columns[2].x * vec.z,
              mat.columns[0].y * vec.x + mat.columns[1].y * vec.y +
                  mat.columns[2].y * vec.z,
              mat.columns[0].z * vec.x + mat.columns[1].z * vec.y +
                  mat.columns[2].z * vec.z);
}

IVY_FORCE_INLINE vec4_t mat4_mul_vec4(mat4_t mat, vec4_t vec) {
  return vec4(mat.columns[0].x * vec.x + mat.columns[1].x * vec.y +
                  mat.columns[2].x * vec.z + mat.columns[3].x * vec.w,
              mat.columns[0].y * vec.x + mat.columns[1].y * vec.y +
                  mat.columns[2].y * vec.z + mat.columns[3].y * vec.w,
              mat.columns[0].z * vec.x + mat.columns[1].z * vec.y +
                  mat.columns[2].z * vec.z + mat.columns[3].z * vec.w,
              mat.columns[0].w * vec.x + mat.columns[1].w * vec.y +
                  mat.columns[2].w * vec.z + mat.columns[3].w * vec.w);
}

IVY_FORCE_INLINE mat2_t mat2_mul(mat2_t a, mat2_t b) {
  mat2_t out = mat2(1.0f);

  out.columns[0] = mat2_mul_vec2(a, b.columns[0]);
  out.columns[1] = mat2_mul_vec2(a, b.columns[1]);

  return out;
}

IVY_FORCE_INLINE mat3_t mat3_mul(mat3_t a, mat3_t b) {
  mat3_t out = mat3(1.0f);

  out.columns[0] = mat3_mul_vec3(a, b.columns[0]);
  out.columns[1] = mat3_mul_vec3(a, b.columns[1]);
  out.columns[2] = mat3_mul_vec3(a, b.columns[2]);

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

static inline mat4_t mat4_trans(vec3_t trans) {
  mat4_t out = mat4(1.0f);
  out.columns[3] = vec4(trans.x, trans.y, trans.z, 1.0f);

  return out;
}

// Generic macros
#define vec_add(a, b)                                                          \
  _Generic((a), vec2_t: vec2_add, vec3_t: vec3_add, vec4_t: vec4_add)((a), (b))

#define vec_sub(a, b)                                                          \
  _Generic((a), vec2_t: vec2_sub, vec3_t: vec3_sub, vec4_t: vec4_sub)((a), (b))

#define vec_mul(a, b)                                                          \
  _Generic((a), vec2_t: vec2_mul, vec3_t: vec3_mul, vec4_t: vec4_mul)((a), (b))

#define vec_div(a, b)                                                          \
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

#define vec_dot(a, b)                                                          \
  _Generic((a), vec2_t: vec2_dot, vec3_t: vec3_dot, vec4_t: vec4_dot)((a), (b))

#define vec_len_sq(vec)                                                        \
  _Generic((vec),                                                              \
      vec2_t: vec2_len_sq,                                                     \
      vec3_t: vec3_len_sq,                                                     \
      vec4_t: vec4_len_sq)((vec))

#define vec_len(vec)                                                           \
  _Generic((vec), vec2_t: vec2_len, vec3_t: vec3_len, vec4_t: vec4_len)((vec))

#define vec_norm(vec)                                                          \
  _Generic((vec), vec2_t: vec2_norm, vec3_t: vec3_norm, vec4_t: vec4_norm)(    \
      (vec))

#define vec_lerp(a, b, t)                                                      \
  _Generic((a), vec2_t: vec2_lerp, vec3_t: vec3_lerp, vec4_t: vec4_lerp)(      \
      (a), (b), (t))

#define vec_dist_sq(a, b)                                                      \
  _Generic((a),                                                                \
      vec2_t: vec2_dist_sq,                                                    \
      vec3_t: vec3_dist_sq,                                                    \
      vec4_t: vec4_dist_sq)((a), (b))

#define vec_dist(a, b)                                                         \
  _Generic((a), vec2_t: vec2_dist, vec3_t: vec3_dist, vec4_t: vec4_dist)((a),  \
                                                                         (b))

#define vec_refl(vec, norm)                                                    \
  _Generic((vec), vec2_t: vec2_refl, vec3_t: vec3_refl, vec4_t: vec4_refl)(    \
      (vec), (norm))

#define mat_mul_vec(mat, vec)                                                  \
  _Generic((mat),                                                              \
      mat2_t: mat2_mul_vec2,                                                   \
      mat3_t: mat3_mul_vec3,                                                   \
      mat4_t: mat4_mul_vec4)((mat), (vec))

#define mat_mul(a, b)                                                          \
  _Generic((a), mat2_t: mat2_mul, mat3_t: mat3_mul, mat4_t: mat4_mul)((a), (b))

#endif
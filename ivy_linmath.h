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

IVY_FORCE_INLINE vec2_t vec2_scalar(float scalar) {
  return (vec2_t){.x = scalar, .y = scalar};
}

IVY_FORCE_INLINE vec3_t vec3_scalar(float scalar) {
  return (vec3_t){.x = scalar, .y = scalar, .z = scalar};
}

IVY_FORCE_INLINE vec4_t vec4_scalar(float scalar) {
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

#ifdef IVY_IMPL

#endif

#endif
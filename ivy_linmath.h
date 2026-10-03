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

#ifdef IVY_IMPL

#endif

#endif
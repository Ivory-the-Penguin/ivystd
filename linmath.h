#ifndef IVY_STD_LINMATH_H
#define IVY_STD_LINMATH_H

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

#ifdef IVY_STD_IMPL

#endif

#endif
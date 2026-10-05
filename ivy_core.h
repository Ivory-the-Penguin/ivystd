/*
  ----- Ivy Core -----
  Version: 0.1.0
  License: MIT-0

  This header only library has useful macro's and stuff for the ivystd.
*/

#ifndef IVY_CORE_H
#define IVY_CORE_H

#define IVY_CORE_MAJOR 0
#define IVY_CORE_MINOR 1
#define IVY_CORE_FIX 0

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if (!defined(__cplusplus) && defined(__STDC_VERSION__))

#if __STDC_VERSION__ >= 199901L
#define IVY_ATLEAST_C99
#endif

#if __STDC_VERSION__ >= 201112L
#define IVY_ATLEAST_C11
#endif

#if __STDC_VERSION__ >= 201710L
#define IVY_ATLEAST_C17
#endif

#if __STDC_VERSION__ >= 202311L
#define IVY_ATLEAST_C23
#endif

#endif

#define IVY_ASSERT(condition, message)                                  \
  ((condition)                                                          \
       ? (void)0                                                        \
       : (fprintf(stderr, "ASSERTION FAILED: %s\nFile: %s, Line: %d\n", \
                  (message), __FILE__, __LINE__),                       \
          abort()))

#if defined(_MSC_VER)
#define IVY_FORCE_INLINE static __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define IVY_FORCE_INLINE static inline __attribute__((always_inline))
#else
#define IVY_FORCE_INLINE static inline
#endif

#endif

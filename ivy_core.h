/*
  ----- Ivy Core -----
  Version: 0.4.0
  License: MIT-0

  This header only library has useful macro's and stuff for the ivystd.
*/

#ifndef IVY_CORE_H
#define IVY_CORE_H

#define IVY_CORE_MAJOR 0
#define IVY_CORE_MINOR 4
#define IVY_CORE_FIX 0

#include <stdarg.h>
#include <stddef.h>
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

#if defined(__GNUC__) || defined(__clang__)
#define IVY_FORCE_INLINE static inline __attribute__((always_inline))
#else
#define IVY_FORCE_INLINE static inline
#endif

#define IVY_CONSTRUCTOR __attribute__((constructor))
#define IVY_DESTRUCTOR __attribute__((destructor))

// Copied with modifications from nostdlib
typedef unsigned char u8;
typedef signed char i8;
typedef unsigned short u16;
typedef signed short i16;
typedef unsigned int u32;
typedef signed int i32;
typedef unsigned long long u64;
typedef signed long long i64;
typedef __SIZE_TYPE__ usize;
typedef signed long isize;
typedef unsigned long uptr;
typedef signed long iptr;
typedef signed long ptrdiff;

typedef __INTMAX_TYPE__ imax;
typedef __UINTMAX_TYPE__ umax;

#define I8_MIN (-128)
#define I16_MIN (-32767 - 1)
#define I32_MIN (-2147483647 - 1)
#define I64_MIN (-9223372036854775807LL - 1)

#define I8_MAX (127)
#define I16_MAX (32767)
#define I32_MAX (2147483647)
#define I64_MAX (9223372036854775807LL)

#define U8_MAX (255)
#define U16_MAX (65535)
#define U32_MAX (4294967295U)
#define U64_MAX (18446744073709551615ULL)

#define SIZE_MAX ((size_t)-1)
#define IPTR_MIN (-__LONG_MAX__ - 1)
#define IPTR_MAX __LONG_MAX__
#define PTRDIFF_MIN IPTR_MIN
#define PTRDIFF_MAX IPTR_MAX
#define UPTR_MAX SIZE_MAX

#define IMAX_MIN I64_MIN
#define IMAX_MAX I64_MAX
#define UMAX_MAX U64_MAX

#ifndef INT_MIN
#define INT_MIN (-__INT_MAX__ - 1)
#endif
#ifndef INT_MAX
#define INT_MAX __INT_MAX__
#endif

#ifndef LONG_MIN
#define LONG_MIN (-__LONG_MAX__ - 1)
#endif
#ifndef LONG_MAX
#define LONG_MAX __LONG_MAX__
#endif

#ifndef ULONG_MAX
#define ULONG_MAX ((unsigned long)(__LONG_MAX__) * 2 + 1)
#endif

#ifndef LLONG_MIN
#define LLONG_MIN (-__LONG_LONG_MAX__ - 1)
#endif
#ifndef LLONG_MAX
#define LLONG_MAX __LONG_LONG_MAX__
#endif

#ifndef ULLONG_MAX
#define ULLONG_MAX ((unsigned long long)(__LONG_LONG_MAX__) * 2 + 1)
#endif

typedef u8 b8;
typedef u16 b16;
typedef u32 b32;

#define true 1
#define false 0

typedef u8 c8;

#define C8_MAX U8_MAX

#endif

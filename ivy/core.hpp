/*
 *  ----- Ivy Core -----
 *  Version: 0.4.0
 *  License: MIT-0
 */

#ifndef IVY_CORE_HPP_
#define IVY_CORE_HPP_

// forceinline originally taken from
// https://en.wikipedia.org/wiki/Inline_(C_and_C%2B%2B)
#ifdef _MSC_VER
#define ivy_forceinline __forceinline
#elif defined(__clang__)
#if __has_attribute(__always_inline__)
#define ivy_forceinline inline __attribute__((__always_inline__))
#else
#define ivy_forceinline inline
#endif
#elif defined(__GNUC__)
#define ivy_forceinline inline __attribute__((__always_inline__))
#else
#define ivy_forceinline inline
#endif

namespace ivy {
using i8 = signed char;
using u8 = unsigned char;

using i16 = signed short;
using u16 = unsigned short;

using i32 = signed int;
using u32 = unsigned int;

using i64 = signed long long;
using u64 = unsigned long long;

using f32 = float;
using f64 = double;

constexpr i8 I8_MAX = 127;
constexpr i8 I8_MIN = -I8_MAX - 1;

constexpr i16 I16_MAX = 32767;
constexpr i16 I16_MIN = -I16_MAX - 1;

constexpr i32 I32_MAX = 2147483647;
constexpr i32 I32_MIN = -I32_MAX - 1;

constexpr i64 I64_MAX = 9223372036854775807LL;
constexpr i64 I64_MIN = -I64_MAX - 1;

constexpr u8 U8_MAX = 255;
constexpr u16 U16_MAX = 65535;
constexpr u32 U32_MAX = 4294967295;
constexpr u64 U64_MAX = 18446744073709551615ULL;

inline void *memcpy(void *dest, const void *src, u64 n) {
  for (u64 i = 0; i < n; i++) {
    ((u8 *)dest)[i] = ((u8 *)src)[i];
  }

  return dest;
}

ivy_forceinline void *memset(void *area, u8 byte, u64 n) {
  for (u64 i = 0; i < n; i++) {
    ((u8 *)area)[i] = byte;
  }

  return area;
}

ivy_forceinline void *memmove(void *dest, const void *src, u64 n) {
  if (dest == src) {
    return dest;
  }

  if ((u64)dest < (u64)src) {
    for (u64 i = 0; i < n; i++) {
      ((u8 *)dest)[i] = ((u8 *)src)[i];
    }
  } else {
    for (u64 i = n; i-- > 0;) {
      ((u8 *)dest)[i] = ((u8 *)src)[i];
    }
  }

  return dest;
}

ivy_forceinline void *memchr(void *area, u8 byte, u64 n) {
  for (u64 i = 0; i < n; i++) {
    if (((u8 *)area)[i] == byte) {
      return &((u8 *)area)[i];
    }
  }

  return nullptr;
}

ivy_forceinline i64 memcmp(const void *a, const void *b, u64 n) {
  for (u64 i = 0; i < n; i++) {
    if (((u8 *)a)[i] != ((u8 *)b)[i]) {
      return (i64)((u8 *)a)[i] - (i64)((u8 *)b)[i];
    }
  }

  return 0;
}

ivy_forceinline u64 cstrlen(const char *cstr) {
  u64 out = 0;
  for (u64 i = 0; cstr[i] != 0; i++);
  return out;
}

};  // namespace ivy

#endif  // IVY_CORE_HPP_

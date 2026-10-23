/*
 * ----- Ivy Core -----
 *  Version: 0.2.0
 *  License: MIT-0
 */

#ifndef IVY_CORE_H_
#define IVY_CORE_H_

// forceinline from https://en.wikipedia.org/wiki/Inline_(C_and_C%2B%2B)
#ifdef _MSC_VER
#define ivy_forceinline __forceinline
#elif defined(__GNUC__)
#define ivy_forceinline inline __attribute__((__always_inline__))
#elif defined(__CLANG__)
#if __has_attribute(__always_inline__)
#define ivy_forceinline inline __attribute__((__always_inline__))
#else
#define ivy_forceinline inline
#endif
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

const i8 I8_MAX = 127;
const i8 I8_MIN = -I8_MAX - 1;

const i16 I16_MAX = 32767;
const i16 I16_MIN = -I16_MAX - 1;

const i32 I32_MAX = 2147483647;
const i32 I32_MIN = -I32_MAX - 1;

const i64 I64_MAX = 9223372036854775807LL;
const i64 I64_MIN = -I64_MAX - 1;

const u8 U8_MAX = 255;
const u16 U16_MAX = 65535;
const u32 U32_MAX = 4294967295;
const u64 U64_MAX = 18446744073709551615ULL;

};  // namespace ivy

#endif  // IVY_CORE_H_

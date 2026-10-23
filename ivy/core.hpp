/*
 * ----- Ivy Core -----
 *  Version: 0.1.0
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

}  // namespace ivy

#endif  // IVY_CORE_H_

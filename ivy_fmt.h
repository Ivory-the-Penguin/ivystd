/*
  ----- Ivy Fmt -----
  Version: 0.1.0
  License: MIT-0

  This stb-style header has a formatting function for ivystd.
  Inspired by the C++ library, {fmt}.

  Use IVY_IMPL macro for implementation
*/

#ifndef IVY_FMT_H
#define IVY_FMT_H

#define IVY_FMT_MAJOR 0
#define IVY_FMT_MINOR 1
#define IVY_FMT_FIX 0

#include "ivy_allocator.h"
#include "ivy_sb.h"
#include "ivy_sv.h"

// Has a secret '\0' in the end.
string_view_t _ivy_fmt_raw(allocator_t alloc, string_view_t fmt, va_list args);

IVY_FORCE_INLINE string_view_t ivy_fmt(allocator_t alloc, string_view_t fmt,
                                       ...) {
  va_list args;
  va_start(args, fmt);
  string_view_t view = _ivy_fmt_raw(alloc, fmt, args);
  va_end(args);
  return view;
}

IVY_FORCE_INLINE void ivy_print(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  string_view_t view = _ivy_fmt_raw(heap, SV(fmt), args);
  va_end(args);

  fwrite(view.data, sizeof(char), view.length, stdout);

  ivy_free(heap, (void *)view.data);
}

IVY_FORCE_INLINE void ivy_print_file(FILE *file, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  string_view_t view = _ivy_fmt_raw(heap, SV(fmt), args);
  va_end(args);

  fwrite(view.data, sizeof(char), view.length, file);

  ivy_free(heap, (void *)view.data);
}

#ifdef IVY_IMPL

string_view_t _ivy_fmt_raw(allocator_t alloc, string_view_t fmt, va_list args) {
  string_builder_t buffer = sb_make(heap);

  while (fmt.length > 0) {
    char chopped = fmt.data[0];
    sv_chop_left(&fmt, 1);

    if (chopped != '{' && chopped != '}') {
      sb_append_char(&buffer, chopped);
      continue;
    }

    if (fmt.length > 0 && fmt.data[0] == chopped) {
      sb_append_char(&buffer, chopped);
      sv_chop_left(&fmt, 1);
      continue;
    }

    string_view_t fmt_option = sv_chop_by_delimiter(&fmt, '}');

    if (sv_compare(fmt_option, SV("s")) == 0) {
      string_view_t str = va_arg(args, string_view_t);
      sb_append_sv(&buffer, str);
    } else if (sv_compare(fmt_option, SV("cs")) == 0) {
      char *str = va_arg(args, char *);
      sb_append_sv(&buffer, SV(str));
    } else if (sv_has_prefix(fmt_option, SV("i"))) {
      sv_chop_left(&fmt_option, 1);

      bool is_unsigned = false;
      bool is_long = false;
      SV_FOREACH(fmt_option, i) {
        switch (fmt_option.data[i]) {
          case 'u':
            is_unsigned = true;
            break;
          case 'l':
            is_long = true;
            break;
          default:
            break;
        }
      }

      uint64_t n;
      if (!is_unsigned) {
        int64_t in_n;
        if (is_long) {
          in_n = va_arg(args, int64_t);
        } else {
          in_n = (int64_t)va_arg(args, int32_t);
        }

        if (in_n < 0) {
          sb_append_char(&buffer, '-');
        }

        n = (in_n < 0 ? -(uint64_t)in_n : (uint64_t)in_n);
      } else {
        if (is_long) {
          n = va_arg(args, uint64_t);
        } else {
          n = (uint64_t)va_arg(args, uint32_t);
        }
      }

      string_view_t n_sv = sv_from_uint(heap, n);

      sb_append_sv(&buffer, n_sv);

      ivy_free(heap, (void *)n_sv.data);
    } else {
      IVY_ASSERT(0, "Unknown formatting specifier!");
    }
  }

  string_view_t out = sb_to_sv(alloc, &buffer);
  sb_free(&buffer);

  return out;
}

#endif

#endif

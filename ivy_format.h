#ifndef IVY_STD_FORMAT_H
#define IVY_STD_FORMAT_H

#include "ivy_allocator.h"
#include "ivy_sb.h"
#include "ivy_sv.h"
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// Has a secret '\0' in the end.
string_view_t _ivy_format_raw(allocator_t alloc, string_view_t fmt,
                              va_list args);

static inline string_view_t ivy_format(allocator_t alloc, string_view_t fmt,
                                       ...) {
  va_list args;
  va_start(args, fmt);
  string_view_t view = _ivy_format_raw(alloc, fmt, args);
  va_end(args);
  return view;
}

static inline void ivy_print(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  string_view_t view = _ivy_format_raw(heap, SV(fmt), args);
  va_end(args);

  fwrite(view.data, sizeof(char), view.length, stdout);

  FREE(heap, (void *)view.data);
}

static inline void ivy_print_file(FILE *file, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  string_view_t view = _ivy_format_raw(heap, SV(fmt), args);
  va_end(args);

  fwrite(view.data, sizeof(char), view.length, file);

  FREE(heap, (void *)view.data);
}

#ifdef IVY_STD_IMPL

string_view_t _ivy_format_raw(allocator_t alloc, string_view_t fmt,
                              va_list args) {
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

      char scratch[32];

      uint64_t length = 0;
      uint64_t temp = n;
      while (temp > 0) {
        length++;
        temp /= 10;
      }
      length = (length == 0 ? 1 : length);

      for (int64_t i = length - 1; i >= 0; i--) {
        scratch[i] = (n % 10) + '0';
        n = n / 10;
      }

      sb_append_sv(&buffer, (string_view_t){.data = scratch, .length = length});
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
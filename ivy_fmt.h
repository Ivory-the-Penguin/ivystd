/*
  ----- Ivy Fmt -----
  Version: 0.2.1
  License: MIT-0

  This stb-style header has a formatting function for ivystd.
  Inspired by the C++ library, {fmt}.

  Use IVY_IMPL macro for implementation
*/

#ifndef IVY_FMT_H
#define IVY_FMT_H

#define IVY_FMT_MAJOR 0
#define IVY_FMT_MINOR 2
#define IVY_FMT_FIX 1

#include "ivy_allocator.h"
#include "ivy_core.h"
#include "ivy_sb.h"
#include "ivy_sv.h"

typedef void (*fmt_func_t)(va_list args, string_builder_t *buffer,
                           string_view_t flags);

typedef struct {
  string_view_t prefix;
  fmt_func_t callback;
} fmt_spec_t;

#define FMT_REGISTRY_MAX 32

void fmt_register(fmt_spec_t spec);

// Has a secret '\0' in the end.
string_view_t _fmt_raw(allocator_t alloc, string_view_t fmt, va_list args);

IVY_FORCE_INLINE string_view_t fmt_format(allocator_t alloc, string_view_t fmt,
                                          ...) {
  va_list args;
  va_start(args, fmt);
  string_view_t view = _fmt_raw(alloc, fmt, args);
  va_end(args);
  return view;
}

IVY_FORCE_INLINE void ivy_print(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  string_view_t view = _fmt_raw(heap, SV(fmt), args);
  va_end(args);

  fwrite(view.data, sizeof(char), view.length, stdout);
  ivy_free(heap, (void *)view.data);
}

IVY_FORCE_INLINE void ivy_print_file(FILE *file, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  string_view_t view = _fmt_raw(heap, SV(fmt), args);
  va_end(args);

  fwrite(view.data, sizeof(char), view.length, file);

  ivy_free(heap, (void *)view.data);
}

#ifdef IVY_IMPL

fmt_spec_t registry[FMT_REGISTRY_MAX] = {0};
uint64_t registry_length = 0;

string_view_t _fmt_raw(allocator_t alloc, string_view_t fmt, va_list args) {
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

    bool found = false;
    for (uint64_t i = 0; i < registry_length; i++) {
      if (sv_has_prefix(fmt_option, registry[i].prefix)) {
        sv_chop_left(&fmt_option, registry[i].prefix.length);
        registry[i].callback(args, &buffer, fmt_option);
        found = true;
        break;
      }
    }

    IVY_ASSERT(found, "Unknown formatting specifier!");
  }

  string_view_t out = sb_to_sv(alloc, &buffer);
  sb_free(&buffer);

  return out;
}

void fmt_register(fmt_spec_t spec) {
  IVY_ASSERT(registry_length != FMT_REGISTRY_MAX,
             "Formatting registry would overflow");
  registry[registry_length++] = spec;
}

IVY_FORCE_INLINE void _fmt_c_string(va_list args, string_builder_t *buffer,
                                    string_view_t flags) {
  (void)flags;
  char *str = va_arg(args, char *);
  sb_append_sv(buffer, SV(str));
}

IVY_FORCE_INLINE void _fmt_int(va_list args, string_builder_t *buffer,
                               string_view_t flags) {
  bool is_unsigned = false;
  bool is_long = false;
  SV_FOREACH(flags, i) {
    switch (flags.data[i]) {
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
      sb_append_char(buffer, '-');
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

  sb_append_sv(buffer, n_sv);

  ivy_free(heap, (void *)n_sv.data);
}

IVY_FORCE_INLINE void _fmt_sv(va_list args, string_builder_t *buffer,
                              string_view_t flags) {
  string_view_t str = va_arg(args, string_view_t);
  sb_append_sv(buffer, str);
}

IVY_CONSTRUCTOR static void fmt_add_builtins() {
  fmt_register((fmt_spec_t){.prefix = SV("cs"), .callback = _fmt_c_string});
  fmt_register((fmt_spec_t){.prefix = SV("i"), .callback = _fmt_int});
  fmt_register((fmt_spec_t){.prefix = SV("s"), .callback = _fmt_sv});
}

#endif

#endif

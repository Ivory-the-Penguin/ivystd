/*
  ----- Ivy Fmt -----
  Version: 1.1.1
  License: MIT-0

  This stb-style header has a formatting function for ivystd.
  Inspired by the C++ library, {fmt}.

  Use IVY_IMPL macro for implementation
*/

#ifndef IVY_FMT_H
#define IVY_FMT_H

#define IVY_FMT_MAJOR 1
#define IVY_FMT_MINOR 1
#define IVY_FMT_FIX 1

#include "ivy_allocator.h"
#include "ivy_sb.h"
#include "ivy_sv.h"

typedef void (*fmt_func_t)(va_list args, string_builder_t *buffer,
                           string_view_t flags, allocator_t scratch);

typedef struct {
  string_view_t prefix;
  fmt_func_t callback;
} fmt_spec_t;

#define FMT_REGISTRY_MAX 32

void fmt_register(string_view_t prefix, fmt_func_t callback);

// Has a secret '\0' in the end.
string_view_t _fmt_raw(allocator_t alloc, string_view_t fmt, va_list args);

string_view_t fmt_format(allocator_t alloc, string_view_t fmt, ...);

void ivy_print(const char *fmt, ...);

void ivy_print_file(FILE *file, const char *fmt, ...);

#ifdef IVY_IMPL

#include "ivy_arena.h"
#include "ivy_core.h"

static arena_t scratch_arena;
static allocator_t scratch_alloc;

IVY_CONSTRUCTOR void _fmt_scratch_init(void) {
  scratch_arena = arena_make(heap);
  scratch_alloc = arena_make_allocator(&scratch_arena);
}

IVY_DESTRUCTOR void _fmt_scratch_clean(void) { arena_free(&scratch_arena); }

fmt_spec_t registry[FMT_REGISTRY_MAX] = {0};
uint64_t registry_length = 0;

string_view_t _fmt_raw(allocator_t alloc, string_view_t fmt, va_list args) {
  string_builder_t buffer = sb_make(heap);
  arena_clear(&scratch_arena);

  while (fmt.length > 0) {
    char chopped = fmt.data[0];
    fmt = sv_chop_left(fmt, 1);

    if (chopped != '{' && chopped != '}') {
      sb_append_char(&buffer, chopped);
      continue;
    }

    if (fmt.length > 0 && fmt.data[0] == chopped) {
      sb_append_char(&buffer, chopped);
      fmt = sv_chop_left(fmt, 1);
      continue;
    }

    string_view_t fmt_option = sv_chop_by_delimiter(&fmt, '}');

    bool found = false;
    for (uint64_t i = 0; i < registry_length; i++) {
      if (sv_has_prefix(fmt_option, registry[i].prefix)) {
        fmt_option = sv_chop_left(fmt_option, registry[i].prefix.length);
        registry[i].callback(args, &buffer, fmt_option, scratch_alloc);
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

string_view_t fmt_format(allocator_t alloc, string_view_t fmt, ...) {
  va_list args;
  va_start(args, fmt);
  string_view_t view = _fmt_raw(alloc, fmt, args);
  va_end(args);
  return view;
}

void ivy_print(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  string_view_t view = _fmt_raw(scratch_alloc, sv(fmt), args);
  va_end(args);

  fwrite(view.data, sizeof(char), view.length, stdout);
}

void ivy_print_file(FILE *file, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  string_view_t view = _fmt_raw(scratch_alloc, sv(fmt), args);
  va_end(args);

  fwrite(view.data, sizeof(char), view.length, file);
}

void fmt_register(string_view_t prefix, fmt_func_t callback) {
  IVY_ASSERT(registry_length != FMT_REGISTRY_MAX,
             "Formatting registry would overflow");

  uint64_t target = 0;
  for (; target < registry_length; target++) {
    if (registry[target].prefix.length < prefix.length) {
      break;
    }
  }

  memmove((void *)(registry + target + 1), (void *)(registry + target),
          sizeof(fmt_spec_t) * (registry_length - target));

  registry[target] = (fmt_spec_t){
      .prefix = prefix,
      .callback = callback,
  };

  registry_length++;
}

IVY_FORCE_INLINE void _fmt_c_string(va_list args, string_builder_t *buffer,
                                    string_view_t flags, allocator_t scratch) {
  (void)flags;
  char *str = va_arg(args, char *);
  sb_append_sv(buffer, sv(str));
}

IVY_FORCE_INLINE void _fmt_int(va_list args, string_builder_t *buffer,
                               string_view_t flags, allocator_t scratch) {
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

  string_view_t n_sv = sv_from_uint(scratch, n);

  sb_append_sv(buffer, n_sv);
}

IVY_FORCE_INLINE void _fmt_sv(va_list args, string_builder_t *buffer,
                              string_view_t flags, allocator_t scratch) {
  string_view_t str = va_arg(args, string_view_t);
  sb_append_sv(buffer, str);
}

IVY_CONSTRUCTOR static void fmt_add_builtins() {
  fmt_register(sv("cs"), _fmt_c_string);
  fmt_register(sv("i"), _fmt_int);
  fmt_register(sv("s"), _fmt_sv);
}

#endif

#endif

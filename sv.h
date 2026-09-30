// Define IVYSTD_IMPL for implementation
// Read https://github.com/nothings/stb/blob/master/docs/stb_howto.txt for
// details

#ifndef IVYSTD_SV_H
#define IVYSTD_SV_H

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "allocator.h"
#include "assert.h"

typedef struct {
  const char *data;
  uint64_t length;
} string_view_t;

#define SV(c_str)                                                              \
  (string_view_t) { .data = c_str, .length = strlen(c_str), }

#define SV_FOREACH(sv, i) for (uint64_t(i) = 0; (i) < (sv.length); (i)++)
#define SV_FOREACH_REV(sv, i) for (uint64_t(i) = sv.length - 1; (i) >= 0; (i)--)

#define SV_FMT "%.*s"

/*
-1 means a is smaller than b,
0 means a is equal to b,
1 means a is bigger than b,
*/
static inline int8_t sv_compare(string_view_t a, string_view_t b) {
  int cmp = memcmp(a.data, b.data, (a.length < b.length ? a.length : b.length));

  if (cmp == 0) {
    if (a.length == b.length) {
      return 0;
    }

    return (a.length > b.length ? 1 : -1);
  }

  return (cmp > 0 ? 1 : -1);
}

static inline bool sv_has_prefix(string_view_t sv, string_view_t prefix) {
  if (prefix.length > sv.length) {
    return false;
  }

  return memcmp(sv.data, prefix.data, prefix.length) == 0;
}

static inline void sv_chop_left(string_view_t *sv, uint64_t n) {
  IVY_ASSERT(sv->length >= n, "String view is too small to be chopped");
  sv->data += n;
  sv->length -= n;
}

static inline void sv_chop_right(string_view_t *sv, uint64_t n) {
  IVY_ASSERT(sv->length >= n, "String view is too small to be chopped");
  sv->length -= n;
}

static inline void sv_trim_left(string_view_t *sv) {
  while (sv->length > 0 && isspace((unsigned char)sv->data[0])) {
    sv_chop_left(sv, 1);
  }
}

static inline void sv_trim_right(string_view_t *sv) {
  while (sv->length > 0 && isspace((unsigned char)sv->data[sv->length - 1])) {
    sv_chop_right(sv, 1);
  }
}

static inline void sv_trim(string_view_t *sv) {
  sv_trim_left(sv);
  sv_trim_right(sv);
}

string_view_t sv_chop_by_delimiter(string_view_t *sv, char delimiter);

// is_type is what IS a delimiter
string_view_t sv_chop_by_type(string_view_t *sv, int (*is_type)(int c));

// is_type is what ISN'T a delimiter
string_view_t sv_chop_by_type_rev(string_view_t *sv, int (*is_type)(int c));

int64_t sv_to_int(string_view_t sv);
uint64_t sv_to_uint(string_view_t sv);

string_view_t sv_from_int(allocator_t alloc, int64_t n);
string_view_t sv_from_uint(allocator_t alloc, uint64_t n);

#ifdef IVYSTD_IMPL

string_view_t sv_chop_by_delimiter(string_view_t *sv, char delimiter) {
  while (sv->length > 0 && sv->data[0] == delimiter) {
    sv_chop_left(sv, 1);
  }

  if (sv->length == 0) {
    return *sv;
  }

  uint64_t end = 0;
  do {
    end++;
  } while (end < sv->length && sv->data[end] != delimiter);

  string_view_t out;
  if (end < sv->length) {
    out = (string_view_t){
        .data = sv->data,
        .length = end,
    };
    sv_chop_left(sv, end + 1);
    return out;
  }

  out = *sv;
  sv_chop_left(sv, sv->length);
  return out;
}

// is_type is what IS a delimiter
string_view_t sv_chop_by_type(string_view_t *sv, int (*is_type)(int c)) {
  while (sv->length > 0 && is_type((unsigned char)sv->data[0])) {
    sv_chop_left(sv, 1);
  }

  if (sv->length == 0) {
    return *sv;
  }

  uint64_t end = 0;
  do {
    end++;
  } while (end < sv->length && !is_type((unsigned char)sv->data[end]));

  string_view_t out;
  if (end < sv->length) {
    out = (string_view_t){
        .data = sv->data,
        .length = end,
    };
    sv_chop_left(sv, end + 1);
    return out;
  }

  out = *sv;
  sv_chop_left(sv, sv->length);
  return out;
}

// is_type is what ISN'T a delimiter
string_view_t sv_chop_by_type_rev(string_view_t *sv, int (*is_type)(int c)) {
  while (sv->length > 0 && !is_type((unsigned char)sv->data[0])) {
    sv_chop_left(sv, 1);
  }

  if (sv->length == 0) {
    return *sv;
  }

  uint64_t end = 0;
  do {
    end++;
  } while (end < sv->length && is_type((unsigned char)sv->data[end]));

  string_view_t out;
  if (end < sv->length) {
    out = (string_view_t){
        .data = sv->data,
        .length = end,
    };
    sv_chop_left(sv, end + 1);
    return out;
  }

  out = *sv;
  sv_chop_left(sv, sv->length);
  return out;
}

#define INT64_MAX_DIV_10 (INT64_MAX / 10)

int64_t sv_to_int(string_view_t sv) {
  SV_FOREACH(sv, i) {}

  bool is_negative = (sv.data[0] == '-');
  sv_chop_left(&sv, is_negative);

  IVY_ASSERT(sv.length <= 19, "The string view is too big to be an integer");

  int64_t out = 0;
  SV_FOREACH(sv, i) {
    char c = sv.data[i];

    IVY_ASSERT(isdigit(c),
               "String view can't contain a nonnumerical character, or a "
               "negative in the wrong place");

    int64_t digit = sv.data[i] - '0';

    IVY_ASSERT(out <= INT64_MAX_DIV_10 + (int64_t)is_negative,
               "Integer would overflow");

    out = (out * 10) + digit;
  }

  return (is_negative ? -out : out);
}

uint64_t sv_to_uint(string_view_t sv) {}

string_view_t sv_from_int(allocator_t alloc, int64_t n);
string_view_t sv_from_uint(allocator_t alloc, uint64_t n);

#endif

#endif
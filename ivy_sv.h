/*
  ----- Ivy String View -----
  Version: 1.2.0
  License: MIT-0

  This stb-style header has a feature-full string view for the ivystd.

  Use IVY_IMPL macro for implementation

  ----- Usage -----
  We have a string_view_t, which contains a pointer to the original data and the
  length. To go through every character, you would use:
  SV_FOREACH(sv, i) {
    putchar(sv.data[i]);
  }

  Or the reverse variation:
  SV_FOREACH_REV(sv, i) {
    putchar(sv.data[i]);
  }

  To make a string view from a string literal / c string, you use the sv func:
  string_view_t sv = sv("Hello, World!");

  And from any string with a custom length:
  string_view_t sv = (string_view_t) {
    .data = str,
    .length = str_len,
  };

  All of the builtin string view functions start with a sv_ prefix. We have the
  following functions:

  ~ sv_compare(a, b) : Compares a and b lexicographically

  ~ sv_has_prefix(sv, prefix) : Check if the sv has a prefix of prefix

  ~ sv_chop_left(sv, n) : Returns sv with the left side chopped by n chars.

  ~ sv_chop_right(sv, n) : Returns sv with the right side chopped by n chars.

  ~ sv_trim_left(sv) : Returns sv with the left side trimmed of whitespaces.

  ~ sv_trim_right(sv) : Returns sv with the right side trimmed of whitespaces.

  ~ sv_trim(sv) : Returns sv with both sides trimmed of whitespaces.

  ~ sv_combine(alloc, a, b) : Returns a and b concatenated, allocated with alloc

  ~ sv_chop_by_delimiter(*sv, delimiter) : Returns a string view which was taken
  from the start of sv to the delimiter, and modifies sv to be right afterwards
  (also consumes the delimiter). It frees any instances of the delimiter at the
  beginning (greedy chopping, like strtok).

  ~ sv_chop_by_type(*sv, is_type) : Same as sv_chop_by_delimiter, but the
  delimiter is defined by the is_type function (int taken in, and int returned).

  ~ sv_chop_by_type_rev(*sv, is_type) : Same as sv_chop_by_type, BUT, the
  is_type function determines what ISN'T a delimiter. So you can use isalpha to
  chop until we reach a non-alphabetic character.

  ~ sv_to_int(sv) : Returns a string view converted into a 64-bit
  signed integer.

  ~ sv_to_uint(sv) : Returns a string view converted into a 64-bit
  unsigned integer.

  ~ sv_from_int(alloc, n) : Returns a 64-bit signed integer n converted into a
  string view, allocated with the alloc. It has a secret null terminator at the
  end.

  ~ sv_from_uint(alloc, n) : Returns a 64-bit unsigned integer n converted into
  a string view, allocated with the alloc. It has a secret null terminator at
  the end.

  ----- Credits -----
  The initial implementation was a copied from Tsoding's video, "C Strings are
  Terrible!" (https://www.youtube.com/watch?v=y8PLpDgZc0E). You can technically
  view this as an expanded version of his implementation.
*/

#ifndef IVY_SV_H
#define IVY_SV_H

#define IVY_SV_MAJOR 1
#define IVY_SV_MINOR 2
#define IVY_SV_FIX 0

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "ivy_allocator.h"
#include "ivy_core.h"

typedef struct {
  const char *data;
  uint64_t length;
} string_view_t;

#define SV_FOREACH(sv, i) for (uint64_t(i) = 0; (i) < (sv.length); (i)++)
#define SV_FOREACH_REV(sv, i) for (int64_t(i) = sv.length - 1; (i) >= 0; (i)--)

#define SV_FMT "%.*s"

// Only for c strings. If you need a sv, just manually create the string view
IVY_FORCE_INLINE string_view_t sv(const char *c_str) {
  return (string_view_t){
      .data = c_str,
      .length = strlen(c_str),
  };
}

/*
-1 means a is smaller than b,
0 means a is equal to b,
1 means a is bigger than b,
*/
IVY_FORCE_INLINE int8_t sv_compare(string_view_t a, string_view_t b) {
  int cmp = memcmp(a.data, b.data, (a.length < b.length ? a.length : b.length));

  if (cmp == 0) {
    if (a.length == b.length) {
      return 0;
    }

    return (a.length > b.length ? 1 : -1);
  }

  return (cmp > 0 ? 1 : -1);
}

IVY_FORCE_INLINE bool sv_has_prefix(string_view_t sv, string_view_t prefix) {
  if (prefix.length > sv.length) {
    return false;
  }

  return memcmp(sv.data, prefix.data, prefix.length) == 0;
}

IVY_FORCE_INLINE string_view_t sv_chop_left(string_view_t sv, uint64_t n) {
  IVY_ASSERT(sv.length >= n, "String view is too small to be chopped");
  sv.data += n;
  sv.length -= n;

  return sv;
}

IVY_FORCE_INLINE string_view_t sv_chop_right(string_view_t sv, uint64_t n) {
  IVY_ASSERT(sv.length >= n, "String view is too small to be chopped");
  sv.length -= n;
  return sv;
}

IVY_FORCE_INLINE string_view_t sv_trim_left(string_view_t sv) {
  while (sv.length > 0 && isspace((unsigned char)sv.data[0])) {
    sv = sv_chop_left(sv, 1);
  }

  return sv;
}

IVY_FORCE_INLINE string_view_t sv_trim_right(string_view_t sv) {
  while (sv.length > 0 && isspace((unsigned char)sv.data[sv.length - 1])) {
    sv = sv_chop_right(sv, 1);
  }

  return sv;
}

IVY_FORCE_INLINE string_view_t sv_trim(string_view_t sv) {
  sv = sv_trim_left(sv);
  sv = sv_trim_right(sv);
  return sv;
}

// Has a secret '\0' in the end.
// Recommended to use ivy_format instead of this.
IVY_FORCE_INLINE string_view_t sv_combine(allocator_t alloc, string_view_t a,
                                          string_view_t b) {
  char *new_buffer = (char *)ivy_alloc(alloc, a.length + b.length + 1);
  memcpy(new_buffer, a.data, a.length);
  memcpy(new_buffer + a.length, b.data, b.length);
  new_buffer[a.length + b.length] = '\0';
  return (string_view_t){
      .data = new_buffer,
      .length = a.length + b.length,
  };
}

string_view_t sv_chop_by_delimiter(string_view_t *sv, char delimiter);

// is_type is what IS a delimiter.
string_view_t sv_chop_by_type(string_view_t *sv, int (*is_type)(int c));

// is_type is what ISN'T a delimiter.
string_view_t sv_chop_by_type_rev(string_view_t *sv, int (*is_type)(int c));

int64_t sv_to_int(string_view_t sv);
uint64_t sv_to_uint(string_view_t sv);

// Has a secret '\0' in the end.
string_view_t sv_from_int(allocator_t alloc, int64_t n);
// Has a secret '\0' in the end.
string_view_t sv_from_uint(allocator_t alloc, uint64_t n);

#ifdef IVY_IMPL

string_view_t sv_chop_by_delimiter(string_view_t *sv, char delimiter) {
  while (sv->length > 0 && sv->data[0] == delimiter) {
    *sv = sv_chop_left(*sv, 1);
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
    *sv = sv_chop_left(*sv, end + 1);
    return out;
  }

  out = *sv;
  *sv = sv_chop_left(*sv, sv->length);
  return out;
}

// is_type is what IS a delimiter
string_view_t sv_chop_by_type(string_view_t *sv, int (*is_type)(int c)) {
  while (sv->length > 0 && is_type((unsigned char)sv->data[0])) {
    *sv = sv_chop_left(*sv, 1);
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
    *sv = sv_chop_left(*sv, end + 1);
    return out;
  }

  out = *sv;
  *sv = sv_chop_left(*sv, sv->length);
  return out;
}

// is_type is what ISN'T a delimiter
string_view_t sv_chop_by_type_rev(string_view_t *sv, int (*is_type)(int c)) {
  while (sv->length > 0 && !is_type((unsigned char)sv->data[0])) {
    *sv = sv_chop_left(*sv, 1);
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
    *sv = sv_chop_left(*sv, end + 1);
    return out;
  }

  out = *sv;
  *sv = sv_chop_left(*sv, sv->length);
  return out;
}

#define INT64_MAX_DIV_10 (INT64_MAX / 10)

int64_t sv_to_int(string_view_t sv) {
  IVY_ASSERT(sv.data != NULL && sv.length > 0,
             "String view can't be null or empty!");

  bool is_negative = (sv.data[0] == '-');
  sv = sv_chop_left(sv, is_negative);

  int64_t out = 0;
  SV_FOREACH(sv, i) {
    char c = sv.data[i];

    IVY_ASSERT(isdigit(c),
               "String view can't contain a nonnumerical character, or a "
               "negative in the wrong place");

    int64_t digit = c - '0';

    IVY_ASSERT(out <= INT64_MAX_DIV_10 + (int64_t)is_negative,
               "Integer would overflow");

    if (out == INT64_MAX_DIV_10) {
      IVY_ASSERT(digit <= 7 + is_negative, "Integer would overflow");
    }

    out = (out * 10) + digit;
  }

  return (is_negative ? -out : out);
}

#define UINT64_MAX_DIV_10 (UINT64_MAX / 10)

uint64_t sv_to_uint(string_view_t sv) {
  IVY_ASSERT(sv.data != NULL && sv.length > 0,
             "String view can't be null or empty!");

  uint64_t out = 0;
  SV_FOREACH(sv, i) {
    char c = sv.data[i];

    IVY_ASSERT(isdigit(c),
               "String view can't contain a nonnumerical character, or a "
               "negative");

    int64_t digit = sv.data[i] - '0';

    IVY_ASSERT(out <= UINT64_MAX_DIV_10, "Integer would overflow");

    if (out == UINT64_MAX_DIV_10) {
      IVY_ASSERT(digit <= 5, "Integer would overflow");
    }

    out = (out * 10) + digit;
  }

  return out;
}

string_view_t sv_from_int(allocator_t alloc, int64_t n) {
  bool is_negative = false;
  uint64_t out_n;
  if (n < 0) {
    is_negative = true;
    out_n = -(uint64_t)n;
  } else {
    out_n = (uint64_t)n;
  }

  int64_t length = 0;
  uint64_t temp = out_n;
  while (temp > 0) {
    length++;
    temp /= 10;
  }
  length = (length == 0 ? 0 : length - 1) + is_negative;

  char *buffer = ivy_alloc(alloc, length + 2);

  if (is_negative) {
    buffer[0] = '-';
  }

  for (int64_t i = length - is_negative; i >= 0; i--) {
    *(buffer + i + is_negative) = (out_n % 10) + '0';
    out_n /= 10;
  }

  buffer[length + 1] = '\0';

  return (string_view_t){
      .data = buffer,
      .length = length + 1,
  };
}

string_view_t sv_from_uint(allocator_t alloc, uint64_t n) {
  int64_t length = 0;
  uint64_t temp = n;
  while (temp > 0) {
    length++;
    temp /= 10;
  }
  length = (length == 0 ? 0 : length - 1);

  char *buffer = ivy_alloc(alloc, length + 2);

  for (int64_t i = length; i >= 0; i--) {
    *(buffer + i) = (n % 10) + '0';
    n /= 10;
  }

  buffer[length + 1] = '\0';

  return (string_view_t){
      .data = buffer,
      .length = length + 1,
  };
}

#endif

#endif

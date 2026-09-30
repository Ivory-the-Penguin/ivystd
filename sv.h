// Define IVY_STD_IMPL for implementation
// Read https://github.com/nothings/stb/blob/master/docs/stb_howto.txt for
// details

#ifndef IVY_STD_SV_H
#define IVY_STD_SV_H

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
#define SV_FOREACH_REV(sv, i) for (int64_t(i) = sv.length - 1; (i) >= 0; (i)--)

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

// Has a secret '\0' in the end
static inline string_view_t sv_combine(allocator_t alloc, string_view_t a,
                                       string_view_t b) {
  char *new_buffer = (char *)ALLOC(alloc, a.length + b.length + 1);
  memcpy(new_buffer, a.data, a.length);
  memcpy(new_buffer + a.length, b.data, b.length);
  new_buffer[a.length + b.length] = '\0';
  return (string_view_t){
      .data = new_buffer,
      .length = a.length + b.length,
  };
}

string_view_t sv_chop_by_delimiter(string_view_t *sv, char delimiter);

// is_type is what IS a delimiter
string_view_t sv_chop_by_type(string_view_t *sv, int (*is_type)(int c));

// is_type is what ISN'T a delimiter
string_view_t sv_chop_by_type_rev(string_view_t *sv, int (*is_type)(int c));

int64_t sv_to_int(string_view_t sv);
uint64_t sv_to_uint(string_view_t sv);

// Has a secret '\0' in the end
string_view_t sv_from_int(allocator_t alloc, int64_t n);
// Has a secret '\0' in the end
string_view_t sv_from_uint(allocator_t alloc, uint64_t n);

#ifdef IVY_STD_IMPL

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
  IVY_ASSERT(sv.data != NULL && sv.length > 0,
             "String view can't be null or empty!");

  bool is_negative = (sv.data[0] == '-');
  sv_chop_left(&sv, is_negative);

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
    out_n = (uint64_t)-(int64_t)n;
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

  char *buffer = ALLOC(alloc, length + 2);

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

  char *buffer = ALLOC(alloc, length + 2);

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
#ifndef IVY_STD_SB_H
#define IVY_STD_SB_H

#include "allocator.h"
#include "sv.h"
#include <stdint.h>

typedef struct {
  char *data;
  uint64_t length, capacity;
} string_builder_t;

#define SB_MINIMUM_CAPACITY 16

static inline string_builder_t sb_make_with_reserved(uint64_t capacity) {
  return (string_builder_t){
      .data = (char *)ALLOC(heap, capacity * sizeof(char)),
      .capacity = capacity,
      .length = 0,
  };
}

static inline string_builder_t sb_make_from_sv(string_view_t sv) {
  string_builder_t sb = sb_make_with_reserved(sv.length);
  sv.length = sv.length;
  memcpy(sb.data, sv.data, sv.length);

  return sb;
}

static inline string_builder_t sb_make(void) {
  return sb_make_with_reserved(SB_MINIMUM_CAPACITY);
}

static inline void sb_free(string_builder_t *sb) {
  FREE(heap, sb->data);
  sb->data = NULL;
  sb->length = 0;
  sb->capacity = 0;
}

#endif
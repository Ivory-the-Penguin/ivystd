#ifndef IVY_STD_SB_H
#define IVY_STD_SB_H

#include "allocator.h"
#include "assert.h"
#include "sv.h"
#include <stdint.h>
#include <string.h>

typedef struct {
  char *data;
  uint64_t length;
  uint64_t capacity;
} string_builder_t;

#define SB_MINIMUM_CAPACITY 16

static inline string_builder_t sb_make_with_reserved(uint64_t capacity) {
  IVY_ASSERT(capacity > 0, "Capacity can't be zero");

  return (string_builder_t){
      .data = (char *)ALLOC(heap, capacity * sizeof(char)),
      .capacity = capacity,
      .length = 0,
  };
}

static inline string_builder_t sb_make_from_sv(string_view_t sv) {
  IVY_ASSERT(sv.data != NULL, "String view is NULL");
  IVY_ASSERT(sv.length > 0, "String view can't be empty. Use "
                            "sb_make_with_reserved or sb_make instead");

  string_builder_t sb = sb_make_with_reserved(sv.length);
  sb.length = sv.length;
  memcpy(sb.data, sv.data, sv.length);

  return sb;
}

static inline string_builder_t sb_make(void) {
  return sb_make_with_reserved(SB_MINIMUM_CAPACITY);
}

static inline void sb_free(string_builder_t *sb) {
  IVY_ASSERT(sb->data != NULL && sb->capacity > 0,
             "String builder can't be uninitialized or freed");

  FREE(heap, sb->data);
  sb->data = NULL;
  sb->length = 0;
  sb->capacity = 0;
}

static inline void sb_expand(string_builder_t *sb, uint64_t capacity) {
  IVY_ASSERT(sb->capacity < capacity, "New capacity has to be bigger than old");

  sb->data = (char *)realloc(sb->data, capacity);
  sb->capacity = capacity;
}

#endif
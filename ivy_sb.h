#ifndef IVY_SB_H
#define IVY_SB_H

#include "ivy_allocator.h"
#include "ivy_core.h"
#include "ivy_sv.h"
#include <stdint.h>
#include <string.h>

typedef struct {
  char *data;
  uint64_t length;
  uint64_t capacity;
  allocator_t alloc;
} string_builder_t;

#define SB_MINIMUM_CAPACITY 16

IVY_FORCE_INLINE string_builder_t sb_make_with_reserved(allocator_t alloc,
                                                        uint64_t capacity) {
  IVY_ASSERT(capacity > 0, "Capacity can't be zero");

  return (string_builder_t){
      .data = (char *)ALLOC(alloc, capacity * sizeof(char)),
      .capacity = capacity,
      .length = 0,
      .alloc = alloc,
  };
}

IVY_FORCE_INLINE string_builder_t sb_make_from_sv(allocator_t alloc,
                                                  string_view_t sv) {
  IVY_ASSERT(sv.data != NULL, "String view is NULL");
  IVY_ASSERT(sv.length > 0, "String view can't be empty. Use "
                            "sb_make_with_reserved or sb_make instead");

  string_builder_t sb = sb_make_with_reserved(alloc, sv.length);
  sb.length = sv.length;
  memcpy(sb.data, sv.data, sv.length);

  return sb;
}

IVY_FORCE_INLINE string_builder_t sb_make(allocator_t alloc) {
  return sb_make_with_reserved(alloc, SB_MINIMUM_CAPACITY);
}

IVY_FORCE_INLINE void sb_free(string_builder_t *sb) {
  IVY_ASSERT(sb->data != NULL && sb->capacity > 0,
             "String builder can't be uninitialized or freed");

  FREE(sb->alloc, sb->data);
  sb->data = NULL;
  sb->length = 0;
  sb->capacity = 0;
}

IVY_FORCE_INLINE void sb_expand(string_builder_t *sb, uint64_t capacity) {
  IVY_ASSERT(sb->capacity < capacity, "New capacity has to be bigger than old");

  sb->data = (char *)REALLOC(sb->alloc, sb->data,
                             ALIGN_BYTES(capacity * sizeof(char)));
  sb->capacity = ALIGN_BYTES(capacity);
}

IVY_FORCE_INLINE void sb_append_char(string_builder_t *sb, char c) {
  if (sb->length + 1 > sb->capacity) {
    sb_expand(sb, sb->capacity * 2);
  }

  sb->data[sb->length++] = c;
}

IVY_FORCE_INLINE void sb_append_sv(string_builder_t *sb, string_view_t sv) {
  if (sb->length + sv.length > sb->capacity) {
    sb_expand(sb, sb->length + sv.length);
  }

  memcpy(sb->data + sb->length, sv.data, sv.length);
  sb->length += sv.length;
}

// Use this sparingly
IVY_FORCE_INLINE void sb_pop(string_builder_t *sb, uint64_t amount) {
  IVY_ASSERT(amount <= sb->length,
             "Popping amount exceeds string builder length");

  memset(sb->data + sb->length - amount, 0, amount);
  sb->length -= amount;
}

IVY_FORCE_INLINE string_view_t sb_to_sv(allocator_t alloc,
                                        string_builder_t *sb) {
  char *buffer = (char *)ALLOC(alloc, sb->length + 1);

  memcpy(buffer, sb->data, sb->length);
  buffer[sb->length] = '\0';

  return (string_view_t){
      .data = buffer,
      .length = sb->length,
  };
}

#endif
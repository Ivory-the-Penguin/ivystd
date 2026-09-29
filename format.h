#ifndef IVYSTD_FORMAT_H
#define IVYSTD_FORMAT_H

#include "allocator.h"
#include "sv.h"
#include <stdarg.h>
#include <string.h>

#define IVY_FORMAT_BUFFER_SIZE 512

// The returned string is hidden null terminating
string_view_t _ivy_format_raw(allocator_t alloc, string_view_t fmt,
                              va_list args) {
  char buffer[IVY_FORMAT_BUFFER_SIZE];
  char *write_cursor = buffer;
  uint64_t bytes_written = 0;

  while (fmt.length > 0) {
    char chopped = fmt.data[0];
    sv_chop_left(&fmt, 1);

    if (chopped != '{' && chopped != '}') {
      *write_cursor++ = chopped;
      bytes_written++;
      continue;
    }

    if (fmt.length > 0 && fmt.data[0] == chopped) {
      *write_cursor++ = chopped;
      bytes_written++;
      sv_chop_left(&fmt, 1);
      continue;
    }
  }

  char *out = (char *)ALLOC(alloc, bytes_written + 1);
  memcpy(out, buffer, bytes_written);
  out[bytes_written] = '\0';

  return (string_view_t){
      .data = out,
      .length = bytes_written,
  };
}

#endif
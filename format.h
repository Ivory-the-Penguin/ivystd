#ifndef IVYSTD_FORMAT_H
#define IVYSTD_FORMAT_H

#include "allocator.h"
#include "sv.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define IVY_FORMAT_BUFFER_SIZE 512

// The returned string is hidden null terminating
string_view_t _ivy_format_raw(allocator_t alloc, string_view_t fmt, ...) {
  va_list args;
  va_start(args, fmt);

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

    string_view_t fmt_option = sv_chop_by_delimiter(&fmt, '}');

    if (sv_compare(fmt_option, SV("s")) == 0) {
      string_view_t str = va_arg(args, string_view_t);
      memcpy(write_cursor, str.data, str.length);
      write_cursor += str.length;
      bytes_written += str.length;
    } else if (sv_compare(fmt_option, SV("cs")) == 0) {
      char *str = va_arg(args, char *);
      uint64_t str_length = strlen(str);
      memcpy(write_cursor, str, str_length);
      write_cursor += str_length;
      bytes_written += str_length;
    }

    printf(SV_FMT "\n", (int)fmt_option.length, fmt_option.data);
  }

  va_end(args);

  char *out = (char *)ALLOC(alloc, bytes_written + 1);
  memcpy(out, buffer, bytes_written);
  out[bytes_written] = '\0';

  return (string_view_t){
      .data = out,
      .length = bytes_written,
  };
}

#endif
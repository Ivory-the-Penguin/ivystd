#ifndef IVYSTD_FORMAT_H
#define IVYSTD_FORMAT_H

#include "allocator.h"
#include "sv.h"
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define IVY_FORMAT_BUFFER_SIZE 512

// The returned string is hidden null terminating
string_view_t _ivy_format_raw(allocator_t alloc, string_view_t fmt, ...) {
  va_list args;
  va_start(args, fmt);

  char buffer[IVY_FORMAT_BUFFER_SIZE];
  char *write_cursor = buffer;

  while (fmt.length > 0) {
    char chopped = fmt.data[0];
    sv_chop_left(&fmt, 1);

    if (chopped != '{' && chopped != '}') {
      *write_cursor++ = chopped;
      continue;
    }

    if (fmt.length > 0 && fmt.data[0] == chopped) {
      *write_cursor++ = chopped;
      sv_chop_left(&fmt, 1);
      continue;
    }

    string_view_t fmt_option = sv_chop_by_delimiter(&fmt, '}');

    if (sv_compare(fmt_option, SV("s")) == 0) {
      string_view_t str = va_arg(args, string_view_t);
      memcpy(write_cursor, str.data, str.length);
      write_cursor += str.length;
    } else if (sv_compare(fmt_option, SV("cs")) == 0) {
      char *str = va_arg(args, char *);
      uint64_t str_length = strlen(str);
      memcpy(write_cursor, str, str_length);
      write_cursor += str_length;
    } else if (sv_compare(fmt_option, SV("i")) == 0) {
      int32_t in_n = va_arg(args, int32_t);

      if (in_n < 0) {
        *write_cursor++ = '-';
      }

      uint32_t n = (in_n < 0 ? (uint32_t)-in_n : (uint32_t)in_n);

      uint64_t length = 0;
      uint64_t temp = n;
      while (temp > 0) {
        length++;
        temp /= 10;
      }
      length = (length == 0 ? 1 : length - 1);

      for (int64_t i = length; i >= 0; i--) {
        *(write_cursor + i) = (n % 10) + '0';
        n = (int)(n / 10);
      }
      write_cursor += length + 1;
    }
  }

  va_end(args);

  uint64_t bytes_written = write_cursor - buffer;
  char *out = (char *)ALLOC(alloc, bytes_written + 1);
  memcpy(out, buffer, bytes_written);
  out[bytes_written] = '\0';

  return (string_view_t){
      .data = out,
      .length = bytes_written,
  };
}

#endif
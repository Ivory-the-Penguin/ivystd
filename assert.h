#ifndef IVY_STD_ASSERT_H
#define IVY_STD_ASSERT_H

#include <stdio.h>
#include <stdlib.h>

#define IVY_ASSERT(condition, message)                                         \
  ((condition)                                                                 \
       ? (void)0                                                               \
       : (fprintf(stderr, "ASSERTION FAILED: %s\nFile: %s, Line: %d\n",        \
                  (message), __FILE__, __LINE__),                              \
          abort()))

#endif

/*
  ----- Ivy Test ------
  Version: 1.0.0
  License: MIT-0

  This stb-style header has testing for the ivystd.
*/

#ifndef IVY_TEST_H
#define IVY_TEST_H

#define IVY_TEST_MAJOR 1
#define IVY_TEST_MINOR 0
#define IVY_TEST_FIX 0

#include "ivy_core.h"
#include "ivy_fmt.h"

extern __thread u64 tests_passed;
extern __thread u64 total_tests;
extern __thread char *test_msg;

#define TEST_CASE_FMT "[ " ANSI_BOLD "{cs}" ANSI_RESET " ] {cs}\n"
#define TEST_ASSERT_FMT "\tAssert failed! {cs}\n"

#define TEST_CASE_RUNNING ANSI_COLOR_YELLOW "RUNNING" ANSI_RESET
#define TEST_CASE_PASSED ANSI_COLOR_GREEN ANSI_BOLD "PASSED" ANSI_RESET
#define TEST_CASE_FAILED ANSI_COLOR_RED ANSI_BOLD "FAILED" ANSI_RESET

#define TEST_SUITE_BEGIN_FMT \
  "----- " ANSI_COLOR_MAGENTA "{cs}" ANSI_RESET " -----\n"
#define TEST_SUITE_END                                               \
  ivy_print("{iul}/{iul} TESTS {cs}\n\n", tests_passed, total_tests, \
            TEST_CASE_PASSED);

#define TEST_CASE(name) IVY_FORCE_INLINE b8(name)(void)

#define TEST_RUN(name)                                   \
  do {                                                   \
    test_msg = NULL;                                     \
    total_tests++;                                       \
    ivy_print(TEST_CASE_FMT, TEST_CASE_RUNNING, #name);  \
    b8 result = (name)();                                \
    if (result) {                                        \
      ivy_print(TEST_CASE_FMT, TEST_CASE_PASSED, #name); \
      tests_passed++;                                    \
    } else {                                             \
      ivy_print(TEST_CASE_FMT, TEST_CASE_FAILED, #name); \
      if (test_msg) {                                    \
        ivy_print(TEST_ASSERT_FMT, test_msg);            \
      }                                                  \
    }                                                    \
  } while (0)

#define TEST_ASSERT(condition, msg) \
  do {                              \
    if (!(condition)) {             \
      test_msg = msg;               \
      return false;                 \
    }                               \
  } while (0)

#define TEST_OK() \
  do {            \
    return true;  \
  } while (0)

#define TEST_SUITE(name) IVY_FORCE_INLINE void(name)(void)

#define TEST_SUITE_RUN(name)                \
  do {                                      \
    total_tests = 0;                        \
    tests_passed = 0;                       \
    ivy_print(TEST_SUITE_BEGIN_FMT, #name); \
    (name)();                               \
    TEST_SUITE_END                          \
  } while (0)

#ifdef IVY_IMPL

__thread u64 tests_passed;
__thread u64 total_tests;
__thread char *test_msg;

#endif

#endif

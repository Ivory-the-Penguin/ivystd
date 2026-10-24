#include "../ivy_core.h"
#include "../ivy_test.h"

TEST_CASE(core_test_type_sizes) {
  TEST_EXPECT(sizeof(i8), 1, "{i:u}");
  TEST_EXPECT(sizeof(u8), 1, "{i:u}");

  TEST_EXPECT(sizeof(i16), 2, "{i:u}");
  TEST_EXPECT(sizeof(u16), 2, "{i:u}");

  TEST_EXPECT(sizeof(i32), 4, "{i:u}");
  TEST_EXPECT(sizeof(u32), 4, "{i:u}");

  TEST_EXPECT(sizeof(i64), 8, "{i:u}");
  TEST_EXPECT(sizeof(u64), 8, "{i:u}");

  TEST_EXPECT(sizeof(u8), 1, "{i:u}");

  TEST_OK();
}

TEST_SUITE(core_test_suite) { TEST_RUN(core_test_type_sizes); }

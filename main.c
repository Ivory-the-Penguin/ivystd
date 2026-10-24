#define IVY_IMPL

#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "ivy_core.h"
#include "ivy_fmt.h"

i32 main(i32 argc, char *argv[]) {
  u8 arr[5] = {1, 2, 3, 4, 5};

  ivy_print("{i:lu} {i:lu}\n", (u64)&arr[0], (u64)&arr[1]);
}

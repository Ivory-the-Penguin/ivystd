#include <raylib.h>

#define IVY_IMPL
#include "ivy_core.h"
#include "ivy_linmath.h"

i32 main(void) {
  InitWindow(800, 800, "example");
  SetTargetFPS(60);

  vec2_t bg1 = VEC2_ZERO;
  vec2_t bg2 = vec2(1600.0f, 0.0f);

  while (!WindowShouldClose()) {
    bg1.x -= 20.0f;
    bg2.x -= 20.0f;

    if (bg1.x <= -1600) {
      bg1.x = 1600;
    }
    if (bg2.x <= -1600) {
      bg2.x = 1600;
    }

    BeginDrawing();

    ClearBackground(BLACK);

    DrawRectangle((i32)bg1.x, (i32)bg1.y, 1600, 800, RED);
    DrawRectangle((i32)bg2.x, (i32)bg2.y, 1600, 800, BLUE);

    EndDrawing();
  }

  CloseWindow();
}

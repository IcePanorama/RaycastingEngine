#include "map.hpp"

#include <cstdint>
#include <raylib.h>

const uint16_t WINDOW_WIDTH = 1280;
const uint16_t WINDOW_HEIGHT = 720;

/* clang-format off */
uint8_t test_map[64] = {
   1, 1, 1, 1, 1, 1, 1, 1,
   1, 0, 0, 0, 0, 0, 0, 1,
   1, 0, 0, 0, 0, 0, 0, 1,
   1, 0, 0, 1, 1, 0, 0, 1,
   1, 0, 0, 1, 1, 0, 0, 1,
   1, 0, 0, 0, 0, 0, 0, 1,
   1, 0, 0, 0, 0, 0, 0, 1,
   1, 1, 1, 1, 1, 1, 1, 1,
};
/* clang-format on */

// void draw_2d_map (Map &m);

int
main (void)
{
  InitWindow (WINDOW_WIDTH, WINDOW_HEIGHT,
              "Raylib [core] example - basic window");

  while (!WindowShouldClose ())
    {
      BeginDrawing ();
      Map map (8, 8, test_map);
      ClearBackground (RAYWHITE);
      EndDrawing ();
    }

  return 0;
}

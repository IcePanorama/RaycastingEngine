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

void draw_2d_map (Map &m, uint32_t start_x, uint32_t start_y);

int
main (void)
{
  InitWindow (WINDOW_WIDTH, WINDOW_HEIGHT,
              "Raylib [core] example - basic window");

  while (!WindowShouldClose ())
    {
      BeginDrawing ();
      ClearBackground (LIGHTGRAY);
      Map map (8, 8, test_map);
      draw_2d_map (map, 0, 0);
      EndDrawing ();
    }

  return 0;
}

/**
 *  draw_2d_map
 *
 *  Draws a 2D representation of the given map, placing its top right corner at
 *  the given position, `(start_x, start_y)`. Note however, that this function
 *  uses a tiny `GAP_OFFSET` to better visibility, therefore the actual top
 *  right corner of the map on screen will be
 *  `(start_x + GAP_OFFSET / 2, start_y + GAP_OFFSET / 2)`.
 *
 *  @param  m       the map you wish to draw
 *  @param  start_x the x position of the top right corner of the map on screen
 *  @param  start_y the y position of the top right corner of the map on screen
 */
void
draw_2d_map (Map &m, uint32_t start_x, uint32_t start_y)
{
  const uint8_t GAP_OFFSET = 3;
  const Color FLOOR_COLOR = BLACK;
  const Color WALL_COLOR = YELLOW;

  uint8_t width = m.get_width ();
  uint8_t length = m.get_length ();
  const uint8_t SCALE = WINDOW_HEIGHT / length;
  uint8_t size = width * length;

  for (uint8_t i = 0; i < size; i++)
    {
      uint8_t row = i / width;
      uint8_t col = i % width;

      Color c = m.get_map ()[i] == 1 ? WALL_COLOR : FLOOR_COLOR;
      DrawRectangle (start_x + (col * SCALE + GAP_OFFSET),
                     start_y + (row * SCALE + GAP_OFFSET),
                     SCALE - 2 * GAP_OFFSET, SCALE - 2 * GAP_OFFSET, c);
    }
}

#include "map.hpp"
#include "player.hpp"

#include <cstdint>
#include <raylib.h>

const uint16_t WINDOW_WIDTH = 1280;
const uint16_t WINDOW_HEIGHT = 720;

/* clang-format off */
uint8_t test_map[64] = {
   1, 1, 1, 1, 1, 1, 1, 1,
   1, 0, 0, 0, 0, 0, 0, 1,
   1, 0, 0, 0, 0, 0, 0, 1,
   1, 0, 0, 0, 0, 0, 0, 1,
   1, 0, 0, 0, 0, 0, 0, 1,
   1, 0, 0, 0, 0, 0, 0, 1,
   1, 0, 0, 0, 0, 0, 0, 1,
   1, 1, 1, 1, 1, 1, 1, 1,
};
/* clang-format on */

void handle_player_input (void);

int
main (void)
{
  InitWindow (WINDOW_WIDTH, WINDOW_HEIGHT,
              "Raylib [core] example - basic window");

  Map map (8, 8, test_map);
  Player player (WINDOW_WIDTH / 4.0, WINDOW_HEIGHT / 2.0);

  while (!WindowShouldClose ())
    {
      player.handle_player_input ();

      BeginDrawing ();
      ClearBackground (LIGHTGRAY);
      map.draw_2d_map (0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);
      player.draw_player ();
      EndDrawing ();
    }

  return 0;
}

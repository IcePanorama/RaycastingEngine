#include "map.hpp"
#include "player.hpp"

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
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

int
main (void)
{
  InitWindow (WINDOW_WIDTH, WINDOW_HEIGHT, "Raycasting Engine :)");

  Map map (8, 8, test_map);
  Player player (WINDOW_WIDTH / 4.0, WINDOW_HEIGHT / 2.0);

  while (!WindowShouldClose ())
    {
      player.handle_player_input ();

      BeginDrawing ();
      ClearBackground (LIGHTGRAY);
      map.draw_2d_map (0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);

      const double FOV_RADS = player.FOV * DEG2RAD;
      for (int i = WINDOW_WIDTH / 2.0; i < WINDOW_WIDTH; i++)
        {
          double angle
              = player.angle - (FOV_RADS / 2.0)
                + (i - WINDOW_WIDTH / 2.0) * (FOV_RADS / (WINDOW_WIDTH / 2.0));

          float ray_x = std::cosf (angle) * player.view_plane_dist;
          float ray_y = std::sinf (angle) * player.view_plane_dist;
          DrawLineV (player.position,
                     { player.position.x + ray_x, player.position.y + ray_y },
                     GREEN);
        }

      player.draw_player ();
      EndDrawing ();
    }

  return 0;
}

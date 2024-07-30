#include "game_state.hpp"
#include "player.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <raylib.h>

int
main (void)
{
  Player player (Vector2{ 12.0f, 12.0f }, Vector2{ -1.0f, 0.0f },
                 Vector2{ 0.0f, 0.66f });

  InitWindow (SCREEN_WIDTH, SCREEN_HEIGHT, "Raycasting Engine");

  while (!WindowShouldClose ())
    {
      player.handle_input ();

      BeginDrawing ();
      ClearBackground (BLACK);

      for (int x = 0; x < SCREEN_WIDTH; x++)
        {
          // x-coordinate in camera space
          float camera_x = 2 * x / float (SCREEN_WIDTH) - 1;
          Vector2 ray_dir
              = { player.direction.x + player.viewplane.x * camera_x,
                  player.direction.y + player.viewplane.y * camera_x };

          // which map cell we're in
          int map_x = int (player.position.x);
          int map_y = int (player.position.y);

          // len of ray from current pos to next x- or y-side
          Vector2 side_dist = { 0.0f, 0.0f };

          // len of ray from one x- or y-side to the next x- or y-side
          Vector2 delta_dist;
          delta_dist.x = (ray_dir.x == 0) ? 1e30 : std::abs (1 / ray_dir.x);
          delta_dist.y = (ray_dir.y == 0) ? 1e30 : std::abs (1 / ray_dir.y);

          double perp_wall_dist;

          // which directory to step in, x- or y-player.direction (either +1 or
          // -1)
          int step_x, step_y;

          bool hit = false;
          int side; // was a NS or an ES wall hit?

          if (ray_dir.x < 0)
            {
              step_x = -1;
              side_dist.x = (player.position.x - map_x) * delta_dist.x;
            }
          else
            {
              step_x = 1;
              side_dist.x = (map_x + 1.0 - player.position.x) * delta_dist.x;
            }

          if (ray_dir.y < 0)
            {
              step_y = -1;
              side_dist.y = (player.position.y - map_y) * delta_dist.y;
            }
          else
            {
              step_y = 1;
              side_dist.y = (map_y + 1.0 - player.position.y) * delta_dist.y;
            }

          while (!hit)
            {
              if (side_dist.x < side_dist.y)
                {
                  side_dist.x += delta_dist.x;
                  map_x += step_x;
                  side = 0;
                }
              else
                {
                  side_dist.y += delta_dist.y;
                  map_y += step_y;
                  side = 1;
                }
              if (world_map[map_x][map_y] > 0)
                hit = true;
            }

          if (side == 0)
            perp_wall_dist = (side_dist.x - delta_dist.x);
          else
            perp_wall_dist = (side_dist.y - delta_dist.y);

          int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);

          int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
          if (draw_start < 0)
            draw_start = 0;

          int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
          if (draw_end >= SCREEN_HEIGHT)
            draw_end = SCREEN_HEIGHT - 1;

          Color color;
          switch (world_map[map_x][map_y])
            {
            case 1:
              color = RED;
              break;
            case 2:
              color = GREEN;
              break;
            case 3:
              color = BLUE;
              break;
            case 4:
              color = WHITE;
              break;
            default:
              color = YELLOW;
              break;
            }

          if (side == 1)
            color = Color{ (unsigned char)(color.r / 2.0),
                           (unsigned char)(color.g / 2.0),
                           (unsigned char)(color.b / 2.0), color.a };

          DrawLine (x, draw_start, x, draw_end, color);
        }

      DrawFPS (0, 0);
      EndDrawing ();
    }

  return 0;
}

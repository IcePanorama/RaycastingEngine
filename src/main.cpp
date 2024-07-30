#include <cmath>
#include <cstdlib>
#include <iostream>
#include <raylib.h>

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int world_map[MAP_WIDTH][MAP_HEIGHT] = {
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

int
main (void)
{
  Vector2 position = { 12.0f, 12.0f };
  Vector2 direction = { -1.0f, 0.0f };
  Vector2 plane = { 0.0f, 0.66f };

  InitWindow (SCREEN_WIDTH, SCREEN_HEIGHT, "Raycasting Engine");

  while (!WindowShouldClose ())
    {
      double move_speed = 5.0;
      double rot_speed = 3.0 * GetFrameTime ();

      if (IsKeyDown (KEY_W) || IsKeyDown (KEY_UP))
        {
          double move_amount_x = direction.x * move_speed * GetFrameTime ();
          double move_amount_y = direction.y * move_speed * GetFrameTime ();
          if (world_map[(int)(position.x + move_amount_x)][(int)position.y]
              == 0)
            {
              position.x += move_amount_x;
            }
          if (world_map[(int)position.x][(int)(position.y + move_amount_y)]
              == 0)
            {
              position.y += move_amount_y;
            }
        }
      if (IsKeyDown (KEY_S) || IsKeyDown (KEY_DOWN))
        {
          double move_amount_x = direction.x * move_speed * GetFrameTime ();
          double move_amount_y = direction.y * move_speed * GetFrameTime ();
          if (world_map[(int)(position.x - move_amount_x)][(int)position.y]
              == 0)
            {
              position.x -= move_amount_x;
            }
          if (world_map[(int)position.x][(int)(position.y - move_amount_y)]
              == 0)
            {
              position.y -= move_amount_y;
            }
        }
      if (IsKeyDown (KEY_D) || IsKeyDown (KEY_RIGHT))
        {
          double old_dir_x = direction.x;
          direction.x = direction.x * cos (-rot_speed)
                        - direction.y * sin (-rot_speed);
          direction.y
              = old_dir_x * sin (-rot_speed) + direction.y * cos (-rot_speed);
          double old_plane_x = plane.x;
          plane.x = plane.x * cos (-rot_speed) - plane.y * sin (-rot_speed);
          plane.y
              = old_plane_x * sin (-rot_speed) + plane.y * cos (-rot_speed);
        }
      if (IsKeyDown (KEY_A) || IsKeyDown (KEY_LEFT))
        {
          double old_dir_x = direction.x;
          direction.x
              = direction.x * cos (rot_speed) - direction.y * sin (rot_speed);
          direction.y
              = old_dir_x * sin (rot_speed) + direction.y * cos (rot_speed);
          double old_plane_x = plane.x;
          plane.x = plane.x * cos (rot_speed) - plane.y * sin (rot_speed);
          plane.y = old_plane_x * sin (rot_speed) + plane.y * cos (rot_speed);
        }

      BeginDrawing ();
      ClearBackground (BLACK);

      for (int x = 0; x < SCREEN_WIDTH; x++)
        {
          // x-coordinate in camera space
          float camera_x = 2 * x / float (SCREEN_WIDTH) - 1;
          Vector2 ray_dir = { direction.x + plane.x * camera_x,
                              direction.y + plane.y * camera_x };

          // which map cell we're in
          int map_x = int (position.x);
          int map_y = int (position.y);

          // len of ray from current pos to next x- or y-side
          Vector2 side_dist = { 0.0f, 0.0f };

          // len of ray from one x- or y-side to the next x- or y-side
          double delta_dist_x
              = (ray_dir.x == 0) ? 1e30 : std::abs (1 / ray_dir.x);
          double delta_dist_y
              = (ray_dir.y == 0) ? 1e30 : std::abs (1 / ray_dir.y);
          double perp_wall_dist;

          // which directory to step in, x- or y-direction (either +1 or -1)
          int step_x, step_y;

          bool hit = false;
          int side; // was a NS or an ES wall hit?

          if (ray_dir.x < 0)
            {
              step_x = -1;
              side_dist.x = (position.x - map_x) * delta_dist_x;
            }
          else
            {
              step_x = 1;
              side_dist.x = (map_x + 1.0 - position.x) * delta_dist_x;
            }
          if (ray_dir.y < 0)
            {
              step_y = -1;
              side_dist.y = (position.y - map_y) * delta_dist_y;
            }
          else
            {
              step_y = 1;
              side_dist.y = (map_y + 1.0 - position.y) * delta_dist_y;
            }

          while (!hit)
            {
              if (side_dist.x < side_dist.y)
                {
                  side_dist.x += delta_dist_x;
                  map_x += step_x;
                  side = 0;
                }
              else
                {
                  side_dist.y += delta_dist_y;
                  map_y += step_y;
                  side = 1;
                }
              if (world_map[map_x][map_y] > 0)
                hit = true;
            }

          if (side == 0)
            perp_wall_dist = (side_dist.x - delta_dist_x);
          else
            perp_wall_dist = (side_dist.y - delta_dist_y);

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

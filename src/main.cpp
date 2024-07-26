#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ostream>
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
  double pos_x = 12.0;
  double pos_y = 12.0;
  double dir_x = -1.0;
  double dir_y = 0.0;
  double plane_x = 0.0;
  double plane_y = 0.66;

  InitWindow (SCREEN_WIDTH, SCREEN_HEIGHT, "Raycasting Engine");

  while (!WindowShouldClose ())
    {
      std::cout << "FPS: " << GetFPS () << std::endl;

      double move_speed = 5.0;
      double rot_speed = 3.0 * GetFrameTime ();

      if (IsKeyDown (KEY_W) || IsKeyDown (KEY_UP))
        {
          double move_amount_x = dir_x * move_speed * GetFrameTime ();
          double move_amount_y = dir_y * move_speed * GetFrameTime ();
          if (world_map[(int)(pos_x + move_amount_x)][(int)pos_y] == 0)
            {
              pos_x += move_amount_x;
            }
          if (world_map[(int)pos_x][(int)(pos_y + move_amount_y)] == 0)
            {
              pos_y += move_amount_y;
            }
        }
      if (IsKeyDown (KEY_S) || IsKeyDown (KEY_DOWN))
        {
          double move_amount_x = dir_x * move_speed * GetFrameTime ();
          double move_amount_y = dir_y * move_speed * GetFrameTime ();
          if (world_map[(int)(pos_x - move_amount_x)][(int)pos_y] == 0)
            {
              pos_x -= move_amount_x;
            }
          if (world_map[(int)pos_x][(int)(pos_y - move_amount_y)] == 0)
            {
              pos_y -= move_amount_y;
            }
        }
      if (IsKeyDown (KEY_D) || IsKeyDown (KEY_RIGHT))
        {
          double old_dir_x = dir_x;
          dir_x = dir_x * cos (-rot_speed) - dir_y * sin (-rot_speed);
          dir_y = old_dir_x * sin (-rot_speed) + dir_y * cos (-rot_speed);
          double old_plane_x = plane_x;
          plane_x = plane_x * cos (-rot_speed) - plane_y * sin (-rot_speed);
          plane_y
              = old_plane_x * sin (-rot_speed) + plane_y * cos (-rot_speed);
        }
      if (IsKeyDown (KEY_A) || IsKeyDown (KEY_LEFT))
        {
          double old_dir_x = dir_x;
          dir_x = dir_x * cos (rot_speed) - dir_y * sin (rot_speed);
          dir_y = old_dir_x * sin (rot_speed) + dir_y * cos (rot_speed);
          double old_plane_x = plane_x;
          plane_x = plane_x * cos (rot_speed) - plane_y * sin (rot_speed);
          plane_y = old_plane_x * sin (rot_speed) + plane_y * cos (rot_speed);
        }

      BeginDrawing ();
      ClearBackground (BLACK);

      for (int x = 0; x < SCREEN_WIDTH; x++)
        {
          // x-coordinate in camera space
          double camera_x = 2 * x / double (SCREEN_WIDTH) - 1;
          double ray_dir_x = dir_x + plane_x * camera_x;
          double ray_dir_y = dir_y + plane_y * camera_x;

          // which map cell we're in
          int map_x = int (pos_x);
          int map_y = int (pos_y);

          // len of ray from current pos to next x- or y-side
          double side_dist_x, side_dist_y;

          // len of ray from one x- or y-side to the next x- or y-side
          double delta_dist_x
              = (ray_dir_x == 0) ? 1e30 : std::abs (1 / ray_dir_x);
          double delta_dist_y
              = (ray_dir_y == 0) ? 1e30 : std::abs (1 / ray_dir_y);
          double perp_wall_dist;

          // which directory to step in, x- or y-direction (either +1 or -1)
          int step_x, step_y;

          bool hit = false;
          int side; // was a NS or an ES wall hit?

          if (ray_dir_x < 0)
            {
              step_x = -1;
              side_dist_x = (pos_x - map_x) * delta_dist_x;
            }
          else
            {
              step_x = 1;
              side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
            }
          if (ray_dir_y < 0)
            {
              step_y = -1;
              side_dist_y = (pos_y - map_y) * delta_dist_y;
            }
          else
            {
              step_y = 1;
              side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
            }

          while (!hit)
            {
              if (side_dist_x < side_dist_y)
                {
                  side_dist_x += delta_dist_x;
                  map_x += step_x;
                  side = 0;
                }
              else
                {
                  side_dist_y += delta_dist_y;
                  map_y += step_y;
                  side = 1;
                }
              if (world_map[map_x][map_y] > 0)
                hit = true;
            }

          if (side == 0)
            perp_wall_dist = (side_dist_x - delta_dist_x);
          else
            perp_wall_dist = (side_dist_y - delta_dist_y);

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
            color = (Color){ color.r / 2, color.g / 2, color.b / 2, color.a };

          DrawLine (x, draw_start, x, draw_end, color);
        }
      EndDrawing ();
    }

  return 0;
}

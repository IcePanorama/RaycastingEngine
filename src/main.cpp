#include "game_state.hpp"
#include "player.hpp"

#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <raylib.h>
#include <vector>

void cast_rays (Player &p, std::vector<uint32_t> t[8]);
void generate_textures (std::vector<uint32_t> t[8]);

int
main (void)
{
  Player player (Vector2{ 12.0f, 12.0f }, Vector2{ -1.0f, 0.0f },
                 Vector2{ 0.0f, 0.66f });

  std::vector<uint32_t> texture[8];
  for (uint8_t i = 0; i < 8; i++)
    texture[i].resize (TEXTURE_WIDTH * TEXTURE_HEIGHT);

  generate_textures (texture);

  InitWindow (SCREEN_WIDTH, SCREEN_HEIGHT, "Raycasting Engine");

  while (!WindowShouldClose ())
    {
      player.handle_input ();

      BeginDrawing ();
      ClearBackground (BLACK);

      cast_rays (player, texture);

      DrawFPS (0, 0);
      EndDrawing ();
    }

  return 0;
}

void
cast_rays (Player &p, std::vector<uint32_t> t[8])
{
  for (int x = 0; x < SCREEN_WIDTH; x++)
    {
      // x-coordinate in camera space
      float camera_x = 2 * x / float (SCREEN_WIDTH) - 1;
      Vector2 ray_dir = { p.direction.x + p.viewplane.x * camera_x,
                          p.direction.y + p.viewplane.y * camera_x };

      // which map cell we're in
      int map_x = int (p.position.x);
      int map_y = int (p.position.y);

      // len of ray from current pos to next x- or y-side
      Vector2 side_dist = { 0.0f, 0.0f };

      // len of ray from one x- or y-side to the next x- or y-side
      Vector2 delta_dist;
      delta_dist.x = (ray_dir.x == 0) ? 1e30 : std::abs (1 / ray_dir.x);
      delta_dist.y = (ray_dir.y == 0) ? 1e30 : std::abs (1 / ray_dir.y);

      double perp_wall_dist;

      // which directory to step in, x- or y- direction (either +1 or -1)
      int step_x, step_y;

      bool hit = false;
      int side; // was a NS or an ES wall hit?

      if (ray_dir.x < 0)
        {
          step_x = -1;
          side_dist.x = (p.position.x - map_x) * delta_dist.x;
        }
      else
        {
          step_x = 1;
          side_dist.x = (map_x + 1.0 - p.position.x) * delta_dist.x;
        }

      if (ray_dir.y < 0)
        {
          step_y = -1;
          side_dist.y = (p.position.y - map_y) * delta_dist.y;
        }
      else
        {
          step_y = 1;
          side_dist.y = (map_y + 1.0 - p.position.y) * delta_dist.y;
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

      /*
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
       */

      int tex_num = world_map[map_x][map_y] - 1;
      float wall_x;
      if (side == 0)
        wall_x = p.position.y + perp_wall_dist * ray_dir.y;
      else
        wall_x = p.position.x + perp_wall_dist * ray_dir.x;
      wall_x -= floorf (wall_x);

      int tex_x = (int)(wall_x * float (TEXTURE_WIDTH));
      if (side == 0 && ray_dir.x > 0)
        tex_x = TEXTURE_WIDTH - tex_x - 1;
      if (side == 1 && ray_dir.y < 0)
        tex_x = TEXTURE_WIDTH - tex_x - 1;

      float step = 1.0 * TEXTURE_HEIGHT / line_height;
      float tex_pos
          = (draw_start - SCREEN_HEIGHT / 2.0 + line_height / 2.0) * step;
      for (int y = draw_start; y < draw_end; y++)
        {
          int tex_y = (int)tex_pos & (TEXTURE_HEIGHT - 1);
          tex_pos += step;
          uint32_t color = t[tex_num][TEXTURE_HEIGHT * tex_y + tex_x];
          if (side == 1)
            color = (color >> 1) & 8355711;
          Color real_color = Color{ (uint8_t)((color >> 16) & 0xFF),
                                    (uint8_t)((color >> 8) & 0xFF),
                                    (uint8_t)(color & 0xFF), 255 };
          DrawPixel (x, y, real_color);
        }
    }
}

void
generate_textures (std::vector<uint32_t> t[8])
{
  for (uint8_t x = 0; x < TEXTURE_WIDTH; x++)
    {
      for (uint8_t y = 0; y < TEXTURE_HEIGHT; y++)
        {
          uint16_t xor_color
              = (x * 256 / TEXTURE_WIDTH) ^ (y * 256 / TEXTURE_HEIGHT);
          uint16_t y_color = y * 256 / TEXTURE_HEIGHT;
          uint16_t xy_color
              = y * 128 / TEXTURE_HEIGHT + x * 128 / TEXTURE_WIDTH;
          t[0][TEXTURE_WIDTH * y + x]
              = 65536 * 254 * (x != y && x != TEXTURE_WIDTH - y);
          t[1][TEXTURE_WIDTH * y + x]
              = xy_color + 256 * xy_color + 65536 * xy_color;
          t[2][TEXTURE_WIDTH * y + x] = 256 * xy_color + 65536 * xy_color;
          t[3][TEXTURE_WIDTH * y + x]
              = xor_color + 256 * xor_color + 65536 * xor_color;
          t[4][TEXTURE_WIDTH * y + x] = 256 * xor_color;
          t[5][TEXTURE_WIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16);
          t[6][TEXTURE_WIDTH * y + x] = 65536 * y_color;
          t[7][TEXTURE_WIDTH * y + x] = 128 + 256 * 128 + 65536 * 128;
        }
    }
}

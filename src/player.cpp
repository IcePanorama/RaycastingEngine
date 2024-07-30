#include "player.hpp"
#include "game_state.hpp"

#include <cmath>
#include <raylib.h>

Player::Player (Vector2 position, Vector2 direction, Vector2 viewplane)
    : position (position), direction (direction), viewplane (viewplane)
{
  movement_speed = 5.0f;
  rotation_speed = 3.0f;
}

Player::Player (Vector2 position, Vector2 direction, Vector2 viewplane,
                float movement_speed, float rotation_speed)
    : position (position), direction (direction), viewplane (viewplane),
      movement_speed (movement_speed), rotation_speed (rotation_speed)
{
}

void
Player::handle_input (void)
{
  double move_speed = movement_speed;
  double rot_speed = rotation_speed * GetFrameTime ();

  if (IsKeyDown (KEY_W) || IsKeyDown (KEY_UP))
    {
      double move_amount_x = direction.x * move_speed * GetFrameTime ();
      double move_amount_y = direction.y * move_speed * GetFrameTime ();
      if (world_map[(int)(position.x + move_amount_x)][(int)position.y] == 0)
        {
          position.x += move_amount_x;
        }
      if (world_map[(int)position.x][(int)(position.y + move_amount_y)] == 0)
        {
          position.y += move_amount_y;
        }
    }
  if (IsKeyDown (KEY_S) || IsKeyDown (KEY_DOWN))
    {
      double move_amount_x = direction.x * move_speed * GetFrameTime ();
      double move_amount_y = direction.y * move_speed * GetFrameTime ();
      if (world_map[(int)(position.x - move_amount_x)][(int)position.y] == 0)
        {
          position.x -= move_amount_x;
        }
      if (world_map[(int)position.x][(int)(position.y - move_amount_y)] == 0)
        {
          position.y -= move_amount_y;
        }
    }
  if (IsKeyDown (KEY_D) || IsKeyDown (KEY_RIGHT))
    {
      double old_dir_x = direction.x;
      direction.x
          = direction.x * cos (-rot_speed) - direction.y * sin (-rot_speed);
      direction.y
          = old_dir_x * sin (-rot_speed) + direction.y * cos (-rot_speed);
      double old_plane_x = viewplane.x;
      viewplane.x
          = viewplane.x * cos (-rot_speed) - viewplane.y * sin (-rot_speed);
      viewplane.y
          = old_plane_x * sin (-rot_speed) + viewplane.y * cos (-rot_speed);
    }
  if (IsKeyDown (KEY_A) || IsKeyDown (KEY_LEFT))
    {
      double old_dir_x = direction.x;
      direction.x
          = direction.x * cos (rot_speed) - direction.y * sin (rot_speed);
      direction.y
          = old_dir_x * sin (rot_speed) + direction.y * cos (rot_speed);
      double old_plane_x = viewplane.x;
      viewplane.x
          = viewplane.x * cos (rot_speed) - viewplane.y * sin (rot_speed);
      viewplane.y
          = old_plane_x * sin (rot_speed) + viewplane.y * cos (rot_speed);
    }
}

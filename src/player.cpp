#include "player.hpp"

#include <cmath>
#include <cstdint>
#include <raylib.h>

void
Player::draw_player (void)
{
  const Color COLOR = BLUE;
  const uint8_t RADIUS = 10;
  DrawCircle (position.x, position.y, RADIUS, COLOR);

  double half_fov_rads = FOV * DEG2RAD / 2.0;
  Vector2 left_endpoint, right_endpoint;
  left_endpoint.x
      = position.x + std::cos (angle - half_fov_rads) * view_plane_dist;
  left_endpoint.y
      = position.y + std::sin (angle - half_fov_rads) * view_plane_dist;
  right_endpoint.x
      = position.x + std::cos (angle + half_fov_rads) * view_plane_dist;
  right_endpoint.y
      = position.y + std::sin (angle + half_fov_rads) * view_plane_dist;

  DrawLineV (left_endpoint, right_endpoint, COLOR);

  float player_dx = std::cos (angle) * view_plane_dist;
  float player_dy = std::sin (angle) * view_plane_dist;
  DrawLineV (position, { position.x + player_dx, position.y + player_dy },
             COLOR);
}

void
Player::handle_player_input (void)
{
  if (IsKeyDown (KEY_A) || IsKeyDown (KEY_LEFT))
    {
      angle -= DEG2RAD * GetFrameTime () * speed;
      if (angle < 0)
        angle += 2 * PI;
      if (angle > 2 * PI)
        angle -= 2 * PI;
    }
  if (IsKeyDown (KEY_D) || IsKeyDown (KEY_RIGHT))
    {
      angle += DEG2RAD * GetFrameTime () * speed;
      if (angle < 0)
        angle += 2 * PI;
      if (angle > 2 * PI)
        angle -= 2 * PI;
    }
  if (IsKeyDown (KEY_W) || IsKeyDown (KEY_UP))
    {
      position.x += cos (angle) * speed * GetFrameTime ();
      position.y += sin (angle) * speed * GetFrameTime ();
    }
  if (IsKeyDown (KEY_S) || IsKeyDown (KEY_DOWN))
    {
      position.x -= cos (angle) * speed * GetFrameTime ();
      position.y -= sin (angle) * speed * GetFrameTime ();
    }
}

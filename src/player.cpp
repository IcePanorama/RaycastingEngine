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

  float player_dx = std::cos (angle) * (RADIUS * RADIUS);
  float player_dy = std::sin (angle) * (RADIUS * RADIUS);
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

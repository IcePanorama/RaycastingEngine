#include "player.hpp"

Player::Player (Vector2 position, Vector2 direction)
    : position (position), direction (direction)
{
  movement_speed = 5.0f;
  rotation_speed = 3.0f;
}

Player::Player (Vector2 position, Vector2 direction, float movement_speed,
                float rotation_speed)
    : position (position), direction (direction),
      movement_speed (movement_speed), rotation_speed (rotation_speed)
{
}

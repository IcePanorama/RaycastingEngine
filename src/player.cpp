#include "player.hpp"

#include <cstdint>

void
Player::draw_player (void)
{
  const Color COLOR = BLUE;
  const uint8_t RADIUS = 10;
  DrawCircle (position.x, position.y, RADIUS, COLOR);
}

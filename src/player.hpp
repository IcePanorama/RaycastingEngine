#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <raylib.h>

class Player
{
public:
  Vector2 position;
  double angle;

  Player (void) : position ((Vector2){ 0, 0 }), angle (0) {}
  Player (float x, float y) : position ((Vector2){ x, y }), angle (0) {}
  Player (double angle) : angle (angle) {}
  Player (float x, float y, double angle)
      : position ((Vector2){ x, y }), angle (angle)
  {
  }

  ~Player (void) = default;
};

#endif

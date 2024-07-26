#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <raylib.h>

class Player
{
public:
  Vector2 position;
  double angle;
  double speed = 100.0;
  double FOV = PI / 2.0;
  double view_plane_dist = 100;

  Player (void) : position{ 0, 0 }, angle (PI) {}
  Player (double angle) : position{ 0, 0 }, angle (angle) {}
  Player (Vector2 position) : position (position), angle (PI) {}
  Player (Vector2 position, double angle) : position (position), angle (angle)
  {
  }
  Player (float x_pos, float y_pos) : position{ x_pos, y_pos }, angle (PI) {}
  Player (float x_pos, float y_pos, double angle)
      : position{ x_pos, y_pos }, angle (angle)
  {
  }

  void draw_player (void);
  void handle_player_input (void);

  ~Player (void) = default;
};

#endif

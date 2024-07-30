#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <raylib.h>

class Player {
public:
	Vector2 position;
	Vector2 direction;
	float movement_speed;
	float rotation_speed;

	Player(Vector2 position, Vector2 direction);
	Player(Vector2 position, Vector2 direction, float movement_speed, float rotation_speed);
	~Player() = default;
};

#endif

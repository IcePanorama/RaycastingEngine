#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <raylib.h>

class Player {
public:
	Vector2 position;
	Vector2 direction;
	Vector2 viewplane;
	float movement_speed;
	float rotation_speed;

	Player(Vector2 position, Vector2 direction, Vector2 viewplane);
	Player(Vector2 position, Vector2 direction, Vector2 viewplane, float movement_speed, float rotation_speed);
	~Player() = default;
	void handle_input(void);
};

#endif

#ifndef _GAME_STATE_HPP_
#define _GAME_STATE_HPP_

#include <cstdint>

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

const uint16_t SCREEN_WIDTH  = 1280;
const uint16_t SCREEN_HEIGHT = 720;
const uint16_t TEXTURE_WIDTH = 32;
const uint16_t TEXTURE_HEIGHT = 32;

extern int world_map[MAP_WIDTH][MAP_HEIGHT];

#endif

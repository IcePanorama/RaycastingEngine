#include "map.hpp"
#include "player.hpp"

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <raylib.h>
#include <vector>

const uint16_t WINDOW_WIDTH = 1280;
const uint16_t WINDOW_HEIGHT = 720;

/* clang-format off */
uint8_t test_map[12][8] = {
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 1, 1, 0, 0, 0, 1},
   {1, 0, 1, 1, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 0, 0, 0, 0, 0, 0, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
};
/* clang-format on */

void init_map_data (Map &m);
void raycast (Map &m, Player &p);

int
main (void)
{
  InitWindow (WINDOW_WIDTH, WINDOW_HEIGHT, "Raycasting Engine :)");

  Map map (12, 8);
  init_map_data (map);

  Player player (WINDOW_WIDTH / 4.0, WINDOW_HEIGHT / 2.0);

  while (!WindowShouldClose ())
    {
      player.handle_player_input ();

      BeginDrawing ();
      ClearBackground (GRAY);
      map.draw_2d_map (0, 0, (int)(WINDOW_WIDTH / 2.0), WINDOW_HEIGHT);
      player.draw_player ();

      // raycast (map, player);

      EndDrawing ();
    }

  return 0;
}

/*
void
raycast (Map &m, Player &p)
{
}
*/

void
init_map_data (Map &m)
{
  m.map_data = {
    std::vector<uint8_t> (std::begin (test_map[0]), std::end (test_map[0])),
    std::vector<uint8_t> (std::begin (test_map[1]), std::end (test_map[1])),
    std::vector<uint8_t> (std::begin (test_map[2]), std::end (test_map[2])),
    std::vector<uint8_t> (std::begin (test_map[3]), std::end (test_map[3])),
    std::vector<uint8_t> (std::begin (test_map[4]), std::end (test_map[4])),
    std::vector<uint8_t> (std::begin (test_map[5]), std::end (test_map[5])),
    std::vector<uint8_t> (std::begin (test_map[6]), std::end (test_map[6])),
    std::vector<uint8_t> (std::begin (test_map[7]), std::end (test_map[7])),
    std::vector<uint8_t> (std::begin (test_map[8]), std::end (test_map[8])),
    std::vector<uint8_t> (std::begin (test_map[9]), std::end (test_map[9])),
    std::vector<uint8_t> (std::begin (test_map[10]), std::end (test_map[10])),
    std::vector<uint8_t> (std::begin (test_map[11]), std::end (test_map[11])),
  };
}

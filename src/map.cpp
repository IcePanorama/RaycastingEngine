#include "map.hpp"

#include <cstdint>
#include <raylib.h>

Map::Map (uint8_t width, uint8_t length, uint8_t *map)
    : width (width), length (length), map (map)
{
}

uint8_t
Map::get_width (void) const
{
  return this->width;
}

uint8_t
Map::get_length (void) const
{
  return this->length;
}

uint8_t *
Map::get_map (void) const
{
  return this->map;
}

void
Map::draw_2d_map (uint32_t start_x, uint32_t start_y, uint32_t end_x,
                  uint32_t end_y)
{
  const uint8_t GAP_OFFSET = 3;
  const Color FLOOR_COLOR = WHITE;
  const Color WALL_COLOR = YELLOW;

  uint8_t width = get_width ();
  uint8_t length = get_length ();
  const uint8_t LEN_SCALE = (end_y - start_y) / length;
  const uint8_t WIDTH_SCALE = (end_x - start_x) / width;
  uint8_t size = width * length;

  for (uint8_t i = 0; i < size; i++)
    {
      uint8_t row = i / width;
      uint8_t col = i % width;

      Color c = map[i] == 1 ? WALL_COLOR : FLOOR_COLOR;
      DrawRectangle (start_x + (col * WIDTH_SCALE + GAP_OFFSET),
                     start_y + (row * LEN_SCALE + GAP_OFFSET),
                     WIDTH_SCALE - 2 * GAP_OFFSET, LEN_SCALE - 2 * GAP_OFFSET,
                     c);
    }
}

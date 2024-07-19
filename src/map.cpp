#include "map.hpp"

Map::Map (uint8_t width, uint8_t length, uint8_t *map)
{
  this->width = width;
  this->length = length;
  this->map = map;
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

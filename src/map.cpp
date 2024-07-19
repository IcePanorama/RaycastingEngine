#include "map.hpp"

/**
 *  Map::Map
 *
 *  Constructor for the `Map` class.
 *
 *  @param  width   the width of the map
 *  @param  length  the length of the map
 *  @param  map     the actual map data itself
 */
Map::Map (uint8_t width, uint8_t length, uint8_t *map)
{
  this->width = width;
  this->length = length;
  this->map = map;
}

/**
 *  Map::get_width
 *
 *  Returns the width of this map.
 *
 *  @return uint8_t of the map width
 */
uint8_t
Map::get_width (void) const
{
  return this->width;
}

/**
 *  Map::get_length
 *
 *  Returns the length of this map.
 *
 *  @return uint8_t of the map length
 */
uint8_t
Map::get_length (void) const
{
  return this->length;
}

/**
 *  Map::get_map
 *
 *  Returns the underlying array of this map.
 *
 *  @return the underlying map array
 */
uint8_t *
Map::get_map (void) const
{
  return this->map;
}

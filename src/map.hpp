#ifndef _MAP_H_
#define _MAP_H_

#include <cstdint>

/**
 *  Map
 *
 *  Wrapper class that stores the `width` and `length` of a given map as well
 *  as the map itself. Note that for simplicities sake, the map is stored in a
 *  1D array.
 */
class Map
{
  uint8_t width;
  uint8_t length;
  uint8_t *map;

public:
  Map (uint8_t width, uint8_t length, uint8_t *map);

  uint8_t get_width (void) const;
  uint8_t get_length (void) const;
  uint8_t *get_map (void) const;

  ~Map () = default;
};

#endif

#ifndef _MAP_H_
#define _MAP_H_

#include <cstdint>

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

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

  /**
   *  draw_2d_map
   *
   *  Draws a 2D representation of the given map, placing its top right corner
   * at the given position, `(start_x, start_y)`. Note however, that this
   * function uses a tiny `GAP_OFFSET` for better visibility, therefore the
   * actual top right corner of the map on screen will be
   *  `(start_x + GAP_OFFSET / 2, start_y + GAP_OFFSET / 2)`.
   *
   *  @param  start_x x position of the top right corner on screen
   *  @param  start_y y position of the top right corner on screen
   *  @param  end_x   where map drawing should end on x-axis
   *  @param  end_y   where map drawing should end on y-axis
   * screen
   */
  void draw_2d_map (uint32_t start_x, uint32_t start_y, uint32_t end_x,
                    uint32_t end_y);
  ~Map () = default;
};

#endif

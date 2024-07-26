#ifndef _MAP_H_
#define _MAP_H_

#include <cstdint>
#include <vector>

class Map
{
public:
  uint8_t num_rows;
  uint8_t num_cols;
  std::vector<std::vector<uint8_t> > map_data;

  Map (uint8_t num_rows, uint8_t num_cols);

  void draw_2d_map (uint32_t start_x, uint32_t start_y, uint32_t end_x,
                    uint32_t end_y);

  ~Map () = default;
};

#endif

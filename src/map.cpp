#include "map.hpp"

#include <cstdint>
#include <raylib.h>

Map::Map (uint8_t num_rows, uint8_t num_cols)
    : num_rows (num_rows), num_cols (num_cols),
      map_data (num_rows, std::vector<uint8_t> (num_cols))
{
}

void
Map::draw_2d_map (uint32_t start_x, uint32_t start_y, uint32_t end_x,
                  uint32_t end_y)
{
  const uint8_t GAP_OFFSET = 3;
  const Color FLOOR_COLOR = WHITE;
  const Color WALL_COLOR = YELLOW;

  if (num_rows == 0 || num_cols == 0)
    return;

  const uint32_t ROW_SCALE = (end_y - start_y) / num_rows;
  const uint32_t COL_SCALE = (end_x - start_x) / num_cols;

  for (uint8_t i = 0; i < num_rows; i++)
    {
      for (uint8_t j = 0; j < num_cols; j++)
        {
          Color c = map_data[i][j] == 1 ? WALL_COLOR : FLOOR_COLOR;
          DrawRectangle (start_x + (j * COL_SCALE + GAP_OFFSET),
                         start_y + (i * ROW_SCALE + GAP_OFFSET),
                         COL_SCALE - 2 * GAP_OFFSET,
                         ROW_SCALE - 2 * GAP_OFFSET, c);
        }
    }
}

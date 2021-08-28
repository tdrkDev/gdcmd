#include <graphics/gfxlevel.h>
#include <types.h>

gfx_gobj_t char_to_gobj(char ch) {
  switch (ch) {
  case 'o':
    return gobj_default_block;
  case '!':
    return gobj_default_spike;
  default:
    return gobj_blank;
  }
}

void level_string_to_gfx(gdcmd_session_t *data, gfx_level_t *level) {
  int x = 0, y = 0;

  for (y = 0; y < MAX_LEVEL_Y_SIZE; y++) {
    for (x = 0; x <= MAX_LEVEL_X_SIZE; x++) {
      level->gobj[x][y] = char_to_gobj(data->lvl.string_2d[x][y]);
    }
  }
}

/*
 * Divide with rounding up
 * Ex:
 * func(5, 6) = 1
 * func(1, 6) = 1
 * func(0, 6) = 0
 */
int dwru(int divident, int divisor) {
  int temp = divident / divisor;

  if (temp * divisor < divident)
    temp++;

  return temp;
}

/*
 * Get divide rest
 */
int drest(int divident, int divisor) {
  int temp = divident / divisor;

  if (temp * divisor < divident)
    return divident - (temp * divisor);

  return 0;
}

void draw_level_gobj_with_offset(gdcmd_session_t *data, gfx_level_t *level,
                                 int offset[2]) {
  int x = 0, y = 0;
  int map_offset[2];
  int map[2] = {0, 0};

  map_offset[0] = offset[0] % GOBJ_PIXMAP_X_SIZE;
  map_offset[1] = offset[1] % GOBJ_PIXMAP_Y_SIZE;

  int x_max = offset[0] / GOBJ_PIXMAP_X_SIZE +
              dwru(data->fb.term_x, GOBJ_PIXMAP_X_SIZE);
  int y_max = offset[1] / GOBJ_PIXMAP_Y_SIZE +
              dwru(data->fb.term_y, GOBJ_PIXMAP_Y_SIZE);

  printf("\033[1;1H");

  for (y = 0; y < y_max; y++) {
    for (x = offset[0] / GOBJ_PIXMAP_X_SIZE; x <= x_max; x++) {
      dump_gobj(&level->gobj[x][y], map[0] * 6 + 1 - map_offset[0],
                data->fb.term_y + 2 - (map[1] * 3 + 1 - map_offset[1]), data);
      map[0]++;
    }

    map[0] = 0;
    map[1]++;
  }
  map[1] = 0;
}
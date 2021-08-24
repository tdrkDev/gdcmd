#include <errno.h>
#include <level.h>
#include <log.h>
#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <types.h>
#include <unistd.h>

int parse_level_string(char *raw, gdcmd_level_t *data) {
  char raw_2d[MAX_LEVEL_X_SIZE + 1024][MAX_LEVEL_Y_SIZE + 128];
  char tmp[MAX_LEVEL_X_SIZE + 1024][MAX_LEVEL_Y_SIZE + 128];
  long y = 0, x = 0, i = 0, y2 = 0;
  long real_x = 0, real_y = 0;
  int level_start[2], level_end[2];
  bool start_found = false, end_found = false;

  // At first, convert raw data to 2d array
  while (true) {
    if (raw[i] == '\n') {
      y++;
      i++;
      continue;
    }

    if (raw[i] == '\0') {
      break;
    }

    i++;
  }

  LOGI("level Y size: %d\n", y);

  i = 0;
  x = 0;

  while (true) {
    raw_2d[x][y] = raw[i];

    if (raw[i] == '\n') {
      y--;
      i++;
      x = 0;
      continue;
    }

    if (raw[i] == '\0') {
      x = 0;
      y = 0;
      i = 0;
      break;
    }

    x++;
    i++;
  }

  for (y = 0; y < MAX_LEVEL_Y_SIZE; y++) {
    if (start_found && end_found)
      break;

    for (x = 0; x < MAX_LEVEL_X_SIZE; x++) {
      if (raw_2d[x][y] == 'x' && !start_found) {
        LOGI("Start x: %ld, y: %ld\n", x, y);

        level_start[0] = x;
        level_start[1] = y;

        start_found = true;
        break;
      }

      // Be sure, that this is not the same y position
      if (raw_2d[x][y] == 'x' && level_start[0] != x && level_start[1] != y &&
          !end_found) {
        LOGI("End x: %ld, y: %ld\n", x, y);

        level_end[0] = x;
        level_end[1] = y;

        end_found = true;
        break;
      }
    }
  }

  if (!start_found || !end_found) {
    LOGE("Failed to determine level coordinates.\n");
    return -EINVAL;
  }

  // Finally, get only level data
  for (y = level_start[1]; y < level_end[1]; y++) {
    real_x = 0;

    for (x = level_start[0] + 1; x <= level_end[0]; x++) {
      data->string_2d[real_x][real_y] = raw_2d[x][y];
      real_x++;
    }

    real_y++;
  }

  data->end[0] = real_x;
  data->end[1] = real_y;

  LOGI("End: x %d, y %d\n", real_x, real_y);

  return 0;
}

void draw_level(int move_x, gdcmd_session_t *data) {
  int y = 0, x = 0;

  // Copy cropped level to framebuffer
  for (x = move_x; x < move_x + data->fb.term_x; x++)
    for (y = 0; y < data->lvl.end[1]; y++)
      data->fb.display[x - move_x][y] = data->lvl.string_2d[x][y];
}
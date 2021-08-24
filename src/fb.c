#include <errno.h>
#include <level.h>
#include <log.h>
#include <ncurses.h>
#include <player.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <types.h>
#include <unistd.h>

// Get terminal size and check it
void fb_init(gdcmd_session_t *data) {
  struct winsize sz;
  int ret;

  // Get terminal size
  ret = ioctl(fileno(stdout), TIOCGWINSZ, &sz);
  if (ret < 0) {
    LOGE("Failed to get terminal size\n");
    return;
  }

  if (sz.ws_col > MAX_FB_COLUMNS || sz.ws_row > MAX_FB_LINES) {
    LOGE("Too big terminal size\n");
    return;
  }

  if (sz.ws_row < data->lvl.end[1] + 5) {
    LOGE("Too small terminal size or too big level Y size\n");
    return;
  }

  data->fb.term_x = sz.ws_col;
  data->fb.term_y = sz.ws_row;
}

void dump_fb(gdcmd_session_t *data) {
  int x, y;

  for (y = data->lvl.end[1]; y > 0; y--) {
    for (x = 0; x < data->fb.term_x; x++) {
      printf("%c", data->fb.display[x][y]);
    }

    printf("\n");
  }

  if (data->plr.alive)
    printf("\033[%dA", data->lvl.end[1]);
}
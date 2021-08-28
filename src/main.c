#include <errno.h>
#include <graphics/gfxlevel.h>
#include <level.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <types.h>
#include <unistd.h>

long get_millis(void) {
  struct timeval t;

  if (gettimeofday(&t, NULL) == -1)
    return 0;

  const long sec_as_ms = ((long)t.tv_sec) * 1000;
  const long usec_as_ms = ((long)t.tv_usec) / 1000;

  return sec_as_ms + usec_as_ms;
}

int main(int argc, char const *argv[]) {
  int i = 0, ret = 0;
  char raw_lvl[MAX_LEVEL_SIZE];
  char buf;

  FILE *fp;
  gdcmd_session_t *session;

  // Allocate memory for global structure
  session = malloc(sizeof(*session));
  if (!session) {
    LOGE("No memory (base)\n");
    return EINVAL;
  }

  if (argc < 2) {
    LOGE("Level file not specified\n");
    return EINVAL;
  }

  fp = fopen(argv[1], "r");
  if (!fp) {
    LOGE("Can't open level file %s\n", argv[1]);
    return EIO;
  }

  while ((buf = fgetc(fp)) != EOF) {
    raw_lvl[i] = buf;
    i++;
  }

  raw_lvl[i + 1] = '\0';

  fclose(fp);

  ret = parse_level_string(raw_lvl, &session->lvl);
  if (ret) {
    LOGE("Level parse failed: %d\n", ret);
    return ret;
  }

  struct winsize sz;

  // Get terminal size
  ret = ioctl(fileno(stdout), TIOCGWINSZ, &sz);
  if (ret < 0) {
    LOGE("Failed to get terminal size\n");
  }

  session->fb.term_x = sz.ws_col;
  session->fb.term_y = sz.ws_row;

  gfx_level_t *level = malloc(sizeof(gfx_level_t));
  int offset[2] = {0, 0};

  printf("\033[2J");

  level_string_to_gfx(session, level);

  long prev = 0, prevoff = 0;
  int ftime = 20;
  int fps = 60;

  for (offset[0] = 0; offset[0] < session->lvl.end[0] * 6; offset[0]++) {
    prev = get_millis();

    if (prevoff + 72 < offset[0]) {
      ret = ioctl(fileno(stdout), TIOCGWINSZ, &sz);
      if (!ret) {
        session->fb.term_x = sz.ws_col;
        session->fb.term_y = sz.ws_row;
      }

      prevoff = offset[0];
    }

    draw_level_gobj_with_offset(session, level, offset);

    /* For debug: FPS, frametime, percentage */
    printf("\033[5;10H %d FPS (%dms)\n", fps, ftime);
    printf("\033[5;%dH %.2f%c\n", session->fb.term_x - 15,
           ((float)offset[0] / (session->lvl.end[0] * 6)) * 100, '%');

    ftime = (get_millis() - prev) % 1000;

    if (ftime < 20) {
      usleep((20 - ftime) * 2500);
    }

    ftime = (get_millis() - prev) % 1000;
    fps = 1000 / ftime;
  }

  return 0;
}

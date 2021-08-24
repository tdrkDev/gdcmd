#include <errno.h>
#include <fb.h>
#include <level.h>
#include <log.h>
#include <player.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <types.h>
#include <unistd.h>

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

  if (!argv[1]) {
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

  LOGI("If you see some problems with display,\n");
  LOGI("try to do 'clear && clear' in your terminal.\n");

  usleep(2000 * 1000);

  // Create jump pthread

  // Allocate some space to draw user's level
  for (i = 0; i < session->lvl.end[1] + 15; i++)
    printf("\r\n");

  // Move cursor to the start of allocated space
  printf("\033[%dA", session->lvl.end[1] + 10);

  player_init(session);
  fb_init(session);

  // Draw level in 10FPS :)
  for (i = 0; i < session->lvl.end[0]; i++) {
    // Draw level to fb
    draw_level(i, session);

    // If needed, change player y.
    check_player_actions(session);

    // Draw player to fb
    draw_player(session);

    dump_fb(session);

    if (!session->plr.alive) {
      return 0;
    }

    // To get 10FPS
    usleep(100 * 1000);
  }

  return 0;
}

#include <errno.h>
#include <level.h>
#include <log.h>
#include <ncurses.h>
#include <player.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <types.h>
#include <unistd.h>

// Jump mutex
pthread_mutex_t jump_mutex;
pthread_t jump_tid;

// Jump Y graph:
//     oo
//    o  o
// ooo    ooo

void *pthread_jump_start_fn(void *raw_data) {
  gdcmd_session_t *data = raw_data;
  char input;

  while (true) {
    if (fgetc(stdin)) {
      pthread_mutex_lock(&jump_mutex);

      // Clear enter
      printf("\033[1A");

      if (data->plr.grounded && data->plr.alive) {
        data->plr.jmp_steps = 1;
        data->plr.grounded = false;
        data->plr.y++;
      } else if (data->fb.display[10][data->plr.y - 1] != ' ') {
        data->plr.wanna_jump = true;
      }

      pthread_mutex_unlock(&jump_mutex);
    }
  }

  pthread_exit(0);
}

void player_init(gdcmd_session_t *data) {
  pthread_mutex_init(&jump_mutex, NULL);
  pthread_create(&jump_tid, NULL, pthread_jump_start_fn, data);

  data->plr.grounded = true;
  data->plr.alive = true;
  data->plr.y = 2;
  data->plr.jmp_steps = 0;
}

void check_player_actions(gdcmd_session_t *data) {
  if (!data->plr.grounded) {
    if (data->plr.jmp_steps == 1) {
      data->plr.y++;
      data->plr.jmp_steps = 2;
    } else if (data->plr.jmp_steps == 2) {
      data->plr.y++;
      data->plr.jmp_steps = 3;

      if (data->fb.display[10][data->plr.y - 1] != ' ') {
        data->plr.grounded = true;
      }
    } else if (data->plr.jmp_steps == 3) {
      data->plr.jmp_steps = 4;

      if (data->fb.display[10][data->plr.y - 1] != ' ') {
        data->plr.grounded = true;
      }
    } else if (data->plr.jmp_steps >= 4) {
      if (data->fb.display[10][data->plr.y - 1] == ' ') {
        data->plr.jmp_steps++;
        data->plr.y--;
      } else {
        data->plr.jmp_steps = 0;
        data->plr.grounded = true;
      }
    }
  } else if (data->plr.wanna_jump) {
    data->plr.wanna_jump = false;

    data->plr.jmp_steps = 1;
    data->plr.grounded = false;
    data->plr.y++;
  }

  if (data->fb.display[10][data->plr.y] == '!')
    data->plr.alive = false;

  if (data->fb.display[10][data->plr.y - 1] == '!')
    data->plr.alive = false;

  if (data->fb.display[10][data->plr.y] == 'o')
    data->plr.alive = false;

  if (data->fb.display[10][data->plr.y - 1] == ' ' && data->plr.grounded)
    data->plr.y--;
}

void draw_player(gdcmd_session_t *data) {
  data->fb.display[PLAYER_X][data->plr.y] = data->plr.alive ? 'P' : 'X';
}
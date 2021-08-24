#include <stdbool.h>

#ifndef __GDCMD_TYPES_H__
#define __GDCMD_TYPES_H__

// Max level size
#define MAX_LEVEL_X_SIZE 8192
#define MAX_LEVEL_Y_SIZE 96

// Max framebuffer size
#define MAX_FB_COLUMNS 1024
#define MAX_FB_LINES 128

// Max level contents size
#define MAX_LEVEL_SIZE ((MAX_LEVEL_X_SIZE + 1024) * (MAX_LEVEL_Y_SIZE + 128))

// TODO:
// Get right end[] values
// Recreate jump mechanism

typedef struct {
  // End coordinates
  int end[2]; // [0] = x, [1] = y

  // NOTE:  y
  //        |
  //        0-->x
  char string_2d[MAX_LEVEL_X_SIZE][MAX_LEVEL_Y_SIZE];
} gdcmd_level_t;

typedef struct {
  // Is player alive?
  bool alive;

  // Is player on ground?
  bool grounded;

  // If currently in air, but player wants
  // to jump again, request jump after
  // player was grounded
  bool wanna_jump;

  // Jump steps
  // 1: y = 1
  // 2: y = 2
  // 3 - ...: y is going down every frame
  int jmp_steps;

  // Position of the player
  // NOTE: X pos is hardcoded
  int y;
} gdcmd_player_t;

// Framebuffer data
typedef struct {
  // NOTE: y
  //       |
  //       0-->x
  char display[MAX_FB_COLUMNS][MAX_FB_LINES];

  int term_x;
  int term_y;
} gdcmd_fb_t;

typedef struct {
  // File containing level
  char level_file[1024];

  // Level data
  gdcmd_level_t lvl;

  // Player data
  gdcmd_player_t plr;

  // Framebuffer
  gdcmd_fb_t fb;
} gdcmd_session_t;

#endif
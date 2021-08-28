#include <log.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef __GDCMD_TYPES_H__
#define __GDCMD_TYPES_H__

// Max level size
#define MAX_LEVEL_X_SIZE 8192
#define MAX_LEVEL_Y_SIZE 96

// Max level contents size
#define MAX_LEVEL_SIZE ((MAX_LEVEL_X_SIZE + 1024) * (MAX_LEVEL_Y_SIZE + 128))

typedef struct {
  // End coordinates
  int end[2]; // [0] = x, [1] = y

  // NOTE:  y
  //        |
  //        0-->x
  char string_2d[MAX_LEVEL_X_SIZE][MAX_LEVEL_Y_SIZE];
} gdcmd_level_t;

// Terminal data
// Note: now GDCmdFB is legacy
typedef struct {
  int term_x;
  int term_y;
} gdcmd_fb_t;

typedef struct {
  // Level data
  gdcmd_level_t lvl;

  // Terminal
  gdcmd_fb_t fb;
} gdcmd_session_t;

#endif
#include <graphics/common.h>
#include <graphics/pixels.h>
#include <types.h>

#ifndef __GDCMD_GFXPLAYER_H__
#define __GDCMD_GFXPLAYER_H__

#define PLAYER_X 6 * 6

typedef struct {
  int pos;
  bool grounded;
} gfx_player_t;

#endif
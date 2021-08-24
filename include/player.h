#include <types.h>

#ifndef __GDCMD_PLAYER_H__
#define __GDCMD_PLAYER_H__

#define PLAYER_X 10

void check_player_actions(gdcmd_session_t *data);
void draw_player(gdcmd_session_t *data);
void player_init(gdcmd_session_t *data);

#endif
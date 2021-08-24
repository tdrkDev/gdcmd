#include <types.h>

#ifndef __GDCMD_LEVEL_H__
#define __GDCMD_LEVEL_H__

int parse_level_string(char *raw, gdcmd_level_t *data);
void draw_level(int move_x, gdcmd_session_t *data);

#endif
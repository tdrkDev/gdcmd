/*
 * GFX GDCmd tools (level pixmap stuff)
 * ---------------
 * Not associated with FB at all!
 */

#include <graphics/common.h>
#include <graphics/pixels.h>
#include <types.h>

#ifndef __GDCMD_GRAPHICS_LEVEL_H__
#define __GDCMD_GRAPHICS_LEVEL_H__

/* multiplied by 4 because of utf-8 :) */
#define MAX_GFX_LEVEL_X_SIZE (MAX_LEVEL_X_SIZE * GOBJ_PIXMAP_X_SIZE)
#define MAX_GFX_LEVEL_Y_SIZE (MAX_LEVEL_Y_SIZE * GOBJ_PIXMAP_Y_SIZE)

typedef struct {
  gfx_gobj_t gobj[MAX_LEVEL_X_SIZE][MAX_LEVEL_Y_SIZE];
} gfx_level_t;

void draw_level_gobj_with_offset(gdcmd_session_t *data, gfx_level_t *level,
                                 int offset[2]);
void level_string_to_gfx(gdcmd_session_t *data, gfx_level_t *level);

#endif
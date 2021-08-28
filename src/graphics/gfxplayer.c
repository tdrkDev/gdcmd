#include <graphics/gfxlevel.h>
#include <graphics/gfxplayer.h>
#include <types.h>

enum gfx_gobj_type_t check_player_collision(gfx_player_t *player,
                                            gfx_level_t *level) {
  gfx_gobj_t *gobj = &level->gobj[PLAYER_X / 6][player->pos / 3];
}
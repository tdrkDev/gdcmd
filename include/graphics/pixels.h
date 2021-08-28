/*
 * GFX GDCmd tools (pixels stuff)
 * ---------------
 * Not associated with FB at all!
 */

#include <graphics/common.h>

#ifndef __GDCMD_PIXELS_H__
#define __GDCMD_PIXELS_H__

/* Const values */
#define GOBJ_PIXMAP_X_SIZE 6
#define GOBJ_PIXMAP_Y_SIZE 3

#define AOBJ_PIXMAP_X_SIZE 8
#define AOBJ_PIXMAP_Y_SIZE 5

/* Types */
enum gfx_gobj_type_t {
  GFX_GOBJ_ERR, /* uhm maybe we"ll have memory leak o_o */
  GFX_GOBJ_SPIKE = 1,
  GFX_GOBJ_BLOCK,
  GFX_GOBJ_PLAYER,
};

typedef char gfx_pixobj_raw_t;

typedef unsigned int gfx_pixobj_color_t;

typedef struct {
  // Symbol (pixobj_xxxx)
  gfx_pixobj_raw_t *pixdata;

  // Foreground color (RGBA)
  gfx_pixobj_color_t fg;

  // Background color (RGBA)
  gfx_pixobj_color_t bg;
} gfx_pixobj_t;

typedef struct {
  // Top left corner
  int start[COORD_MAX];

  // Bottom right corner
  int end[COORD_MAX];
} gfx_fb_coords_t;

// Game object
typedef struct {
  /* Pixel map */
  gfx_pixobj_t (*data)[GOBJ_PIXMAP_X_SIZE][GOBJ_PIXMAP_Y_SIZE];

  /* Object type */
  enum gfx_gobj_type_t type;

  /* Object coordinates in fb */
  gfx_fb_coords_t pos;
} gfx_gobj_t;

// Animation object
typedef struct {
  /* Pixel map */
  gfx_pixobj_t (*data)[AOBJ_PIXMAP_X_SIZE][AOBJ_PIXMAP_Y_SIZE];

  /* Object type */
  enum gfx_gobj_type_t type;

  /* Object coordinates in fb */
  int fb_coords[COORD_MAX];

  /* Object coordinates in level string */
  int lvl_coords[COORD_MAX];
} gfx_aobj_t;

/* To separate pixels from other variables */
#define CREATE_PIXEL_OBJ(name, symbol)                                         \
  static gfx_pixobj_raw_t pixobj_##name[4] = symbol;

/* Pixel objects */

// " "
CREATE_PIXEL_OBJ(filled_0000, " ");

// "▗"
CREATE_PIXEL_OBJ(filled_0001, "▗");

// "▖"
CREATE_PIXEL_OBJ(filled_0010, "▖");

// "▝"
CREATE_PIXEL_OBJ(filled_0100, "▝");

// "▘"
CREATE_PIXEL_OBJ(filled_1000, "▘");

// "▀"
CREATE_PIXEL_OBJ(filled_1100, "▀");

// "▄"
CREATE_PIXEL_OBJ(filled_0011, "▄");

// "▞"
CREATE_PIXEL_OBJ(filled_0101, "▞");

// "▚"
CREATE_PIXEL_OBJ(filled_1010, "▚");

// "▐"
CREATE_PIXEL_OBJ(filled_1001, "▐");

// "▌"
CREATE_PIXEL_OBJ(filled_0110, "▌");

// "▛"
CREATE_PIXEL_OBJ(filled_1110, "▛");

// "▟"
CREATE_PIXEL_OBJ(filled_0111, "▟");

// "▜"
CREATE_PIXEL_OBJ(filled_1101, "▜");

// "▙"
CREATE_PIXEL_OBJ(filled_1011, "▙");

// "█"
CREATE_PIXEL_OBJ(filled_1111, "█");

// "▓"
CREATE_PIXEL_OBJ(filled_1111_shade75, "▓");

// "▒"
CREATE_PIXEL_OBJ(filled_1111_shade50, "▒");

// "░"
CREATE_PIXEL_OBJ(filled_1111_shade15, "░");

#define CREATE_FULL_COLORED_PIXEL(background, foreground, pixobj...)           \
  { .fg = foreground, .bg = background, .pixdata = pixobj, }

#define CREATE_BG_COLORED_PIXEL(background, pixobj...)                         \
  { .fg = 0x00000000, .bg = background, .pixdata = pixobj, }

#define CREATE_FG_COLORED_PIXEL(foreground, pixobj...)                         \
  { .fg = foreground, .bg = 0x00000000, .pixdata = pixobj, }

#define CREATE_PIXEL(pixobj...)                                                \
  { .fg = 0xFFFFFFFF, .bg = 0x00000000, .pixdata = pixobj, }

/* Pixel maps */

// Creator; NOTE: Y is inverted!
#define CREATE_GAME_OBJECT(name, objtype, pixmap...)                           \
  static gfx_pixobj_t pixmap_##name[GOBJ_PIXMAP_X_SIZE][GOBJ_PIXMAP_Y_SIZE] =  \
      pixmap;                                                                  \
                                                                               \
  static gfx_gobj_t gobj_##name = {                                            \
      .type = objtype,                                                         \
      .pos = {{0, 0}, {0, 0}},                                                 \
      .data = &pixmap_##name,                                                  \
  };

/*
 * default block
 * ----[6x3]----
 * █▀▀▀▀█
 * █    █
 * █▄▄▄▄█
 */
CREATE_GAME_OBJECT(
    default_block, GFX_GOBJ_BLOCK,
    {
        {
            CREATE_FG_COLORED_PIXEL(0xAFBDBDBD, pixobj_filled_1111),
            CREATE_FG_COLORED_PIXEL(0xAFD6D6D6, pixobj_filled_1111),
            CREATE_FG_COLORED_PIXEL(0xAFF0F0F0, pixobj_filled_1111),
        },
        {
            CREATE_FULL_COLORED_PIXEL(0xFF1C273F, 0xAFBDBDBD,
                                      pixobj_filled_0011),
            CREATE_BG_COLORED_PIXEL(0xFF212E49, pixobj_filled_0000),
            CREATE_FULL_COLORED_PIXEL(0xFF2A3B5F, 0xAFF0F0F0,
                                      pixobj_filled_1100),
        },
        {
            CREATE_FULL_COLORED_PIXEL(0xFF1C273F, 0xAFBDBDBD,
                                      pixobj_filled_0011),
            CREATE_BG_COLORED_PIXEL(0xFF212E49, pixobj_filled_0000),
            CREATE_FULL_COLORED_PIXEL(0xFF2A3B5F, 0xAFF0F0F0,
                                      pixobj_filled_1100),
        },
        {
            CREATE_FULL_COLORED_PIXEL(0xFF1C273F, 0xAFBDBDBD,
                                      pixobj_filled_0011),
            CREATE_BG_COLORED_PIXEL(0xFF212E49, pixobj_filled_0000),
            CREATE_FULL_COLORED_PIXEL(0xFF2A3B5F, 0xAFF0F0F0,
                                      pixobj_filled_1100),
        },
        {
            CREATE_FULL_COLORED_PIXEL(0xFF1C273F, 0xAFBDBDBD,
                                      pixobj_filled_0011),
            CREATE_BG_COLORED_PIXEL(0xFF212E49, pixobj_filled_0000),
            CREATE_FULL_COLORED_PIXEL(0xFF2A3B5F, 0xAFF0F0F0,
                                      pixobj_filled_1100),
        },
        {
            CREATE_FG_COLORED_PIXEL(0xAFBDBDBD, pixobj_filled_1111),
            CREATE_FG_COLORED_PIXEL(0xAFD6D6D6, pixobj_filled_1111),
            CREATE_FG_COLORED_PIXEL(0xAFF0F0F0, pixobj_filled_1111),
        },
    });

/*
 * default spike
 * ----[6x3]----
 *   ▟▙
 *  ▟▒▒▙
 * ▟▓▓▓▓▙
 */
CREATE_GAME_OBJECT(
    default_spike, GFX_GOBJ_PLAYER,
    {
        {
            CREATE_FG_COLORED_PIXEL(0xAFBDBDBD, pixobj_filled_0111),
            CREATE_FG_COLORED_PIXEL(0xAFD6D6D6, pixobj_filled_0000),
            CREATE_FG_COLORED_PIXEL(0xAFF0F0F0, pixobj_filled_0000),
        },
        {
            CREATE_FULL_COLORED_PIXEL(0xFF1C273F, 0xAFBDBDBD,
                                      pixobj_filled_1011),
            CREATE_FG_COLORED_PIXEL(0xAFD6D6D6, pixobj_filled_0111),
            CREATE_FG_COLORED_PIXEL(0xAFF0F0F0, pixobj_filled_0000),
        },
        {

            CREATE_FULL_COLORED_PIXEL(0xFF1C273F, 0xAFBDBDBD,
                                      pixobj_filled_0011),
            CREATE_FULL_COLORED_PIXEL(0xFF212E49, 0xAFD6D6D6,
                                      pixobj_filled_1000),
            CREATE_FG_COLORED_PIXEL(0xAFF0F0F0, pixobj_filled_0111),
        },
        {
            CREATE_FULL_COLORED_PIXEL(0xFF1C273F, 0xAFBDBDBD,
                                      pixobj_filled_0011),
            CREATE_FULL_COLORED_PIXEL(0xFF212E49, 0xAFD6D6D6,
                                      pixobj_filled_0100),
            CREATE_FG_COLORED_PIXEL(0xAFF0F0F0, pixobj_filled_1011),
        },
        {
            CREATE_FULL_COLORED_PIXEL(0xFF1C273F, 0xAFBDBDBD,
                                      pixobj_filled_0111),
            CREATE_FG_COLORED_PIXEL(0xAFD6D6D6, pixobj_filled_1011),
            CREATE_FG_COLORED_PIXEL(0xAFF0F0F0, pixobj_filled_0000),
        },
        {
            CREATE_FG_COLORED_PIXEL(0xAFBDBDBD, pixobj_filled_1011),
            CREATE_FG_COLORED_PIXEL(0xAFD6D6D6, pixobj_filled_0000),
            CREATE_FG_COLORED_PIXEL(0xAFF0F0F0, pixobj_filled_0000),
        },
    });

/*
 *  player icon
 * ----[6x3]----
 * █▀▀▀▀█
 * █ ▓▓ █
 * █▄▄▄▄█
 */
CREATE_GAME_OBJECT(
    player_icon, GFX_GOBJ_PLAYER,
    {
        {
            CREATE_FG_COLORED_PIXEL(0xBF3DFF63, pixobj_filled_1111),
            CREATE_FG_COLORED_PIXEL(0xDF3DFF63, pixobj_filled_1111),
            CREATE_FG_COLORED_PIXEL(0xFF3DFF63, pixobj_filled_1111),
        },
        {
            CREATE_FG_COLORED_PIXEL(0xBF3DFF63, pixobj_filled_0011),
            CREATE_PIXEL(pixobj_filled_0000),
            CREATE_FG_COLORED_PIXEL(0xFF3DFF63, pixobj_filled_1100),
        },
        {
            CREATE_FG_COLORED_PIXEL(0xBF3DFF63, pixobj_filled_0011),
            CREATE_FULL_COLORED_PIXEL(0xCF5BDEFF, 0xFF5BDEFF,
                                      pixobj_filled_1100),
            CREATE_FG_COLORED_PIXEL(0xFF3DFF63, pixobj_filled_1100),
        },
        {
            CREATE_FG_COLORED_PIXEL(0xBF3DFF63, pixobj_filled_0011),
            CREATE_FULL_COLORED_PIXEL(0xCF5BDEFF, 0xFF5BDEFF,
                                      pixobj_filled_1100),
            CREATE_FG_COLORED_PIXEL(0xFF3DFF63, pixobj_filled_1100),
        },
        {
            CREATE_FG_COLORED_PIXEL(0xBF3DFF63, pixobj_filled_0011),
            CREATE_PIXEL(pixobj_filled_0000),
            CREATE_FG_COLORED_PIXEL(0xFF3DFF63, pixobj_filled_1100),
        },
        {
            CREATE_FG_COLORED_PIXEL(0xBF3DFF63, pixobj_filled_1111),
            CREATE_FG_COLORED_PIXEL(0xDF3DFF63, pixobj_filled_1111),
            CREATE_FG_COLORED_PIXEL(0xFF3DFF63, pixobj_filled_1111),
        },
    });

CREATE_GAME_OBJECT(blank, GFX_GOBJ_ERR,
                   {
                       {
                           CREATE_PIXEL(pixobj_filled_0000),
                           CREATE_PIXEL(pixobj_filled_0000),
                           CREATE_PIXEL(pixobj_filled_0000),
                       },
                       {
                           CREATE_PIXEL(pixobj_filled_0000),
                           CREATE_PIXEL(pixobj_filled_0000),
                           CREATE_PIXEL(pixobj_filled_0000),
                       },
                       {
                           CREATE_PIXEL(pixobj_filled_0000),
                           CREATE_PIXEL(pixobj_filled_0000),
                           CREATE_PIXEL(pixobj_filled_0000),
                       },
                       {
                           CREATE_PIXEL(pixobj_filled_0000),
                           CREATE_PIXEL(pixobj_filled_0000),
                           CREATE_PIXEL(pixobj_filled_0000),
                       },
                       {
                           CREATE_PIXEL(pixobj_filled_0000),
                           CREATE_PIXEL(pixobj_filled_0000),
                           CREATE_PIXEL(pixobj_filled_0000),
                       },
                       {
                           CREATE_PIXEL(pixobj_filled_0000),
                           CREATE_PIXEL(pixobj_filled_0000),
                           CREATE_PIXEL(pixobj_filled_0000),
                       },
                   });

void print_pixobj(gfx_pixobj_t *pixobj);
void dump_gobj(gfx_gobj_t *gobj, int xp, int yp, gdcmd_session_t *data);

#endif

#include <errno.h>
#include <graphics/pixels.h>
#include <level.h>
#include <log.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <types.h>
#include <unistd.h>

unsigned char get_pixobj_r_color(gfx_pixobj_t *pixobj, bool fg) {
  gfx_pixobj_color_t colorspace = fg ? pixobj->fg : pixobj->bg;

  unsigned char color = (colorspace >> 16) & 0xFF;
  unsigned char alpha = (colorspace >> 24) & 0xFF;

  if (alpha != 0xFF) {
    color = color * alpha / 0xFF;
  }

  return color;
}

unsigned char get_pixobj_g_color(gfx_pixobj_t *pixobj, bool fg) {
  gfx_pixobj_color_t colorspace = fg ? pixobj->fg : pixobj->bg;

  unsigned char color = (colorspace >> 8) & 0xFF;
  unsigned char alpha = (colorspace >> 24) & 0xFF;

  if (alpha != 0xFF) {
    color = color * alpha / 0xFF;
  }

  return color;
}

unsigned char get_pixobj_b_color(gfx_pixobj_t *pixobj, bool fg) {
  gfx_pixobj_color_t colorspace = fg ? pixobj->fg : pixobj->bg;

  unsigned char color = colorspace & 0xFF;
  unsigned char alpha = (colorspace >> 24) & 0xFF;

  if (alpha != 0xFF) {
    color = color * alpha / 0xFF;
  }

  return color;
}

void dump_gobj(gfx_gobj_t *gobj, int xp, int yp, gdcmd_session_t *data) {
  int x_negative_offset = 0;

  if (xp < 1) {
    x_negative_offset = -xp + 1;
    xp = 1;
  }

  for (int y = GOBJ_PIXMAP_Y_SIZE - 1; y >= 0; y--) {
    for (int x = x_negative_offset; x < GOBJ_PIXMAP_X_SIZE; x++) {
      gfx_pixobj_t pixobj = (*gobj->data)[x][y];

      if (xp + x - x_negative_offset > data->fb.term_x) {
        continue;
      }

      if (xp + x - x_negative_offset < 1) {
        continue;
      }

      printf("\033[%d;%dH", yp - y, xp + x - x_negative_offset);

      printf("\033[38;2;%d;%d;%dm", get_pixobj_r_color(&pixobj, true),
             get_pixobj_g_color(&pixobj, true),
             get_pixobj_b_color(&pixobj, true));
      printf("\033[48;2;%d;%d;%dm", get_pixobj_r_color(&pixobj, false),
             get_pixobj_g_color(&pixobj, false),
             get_pixobj_b_color(&pixobj, false));

      printf("%s", pixobj.pixdata);

      printf("\033[38;0m");
      printf("\033[48;0m");
    }
  }
}

void print_pixobj(gfx_pixobj_t *pixobj) {
  printf("\033[38;2;%d;%d;%dm", get_pixobj_r_color(pixobj, true),
         get_pixobj_g_color(pixobj, true), get_pixobj_b_color(pixobj, true));
  printf("\033[48;2;%d;%d;%dm", get_pixobj_r_color(pixobj, false),
         get_pixobj_g_color(pixobj, false), get_pixobj_b_color(pixobj, false));

  printf("%s", pixobj->pixdata);

  printf("\033[38;0m");
  printf("\033[48;0m");
}
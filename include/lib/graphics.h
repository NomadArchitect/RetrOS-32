#ifndef __GRAPHICS_H
#define __GRAPHICS_H

/**
 * @brief Library version of kernel gfxlib
 * 
 */

enum gfx_lib_api_options {
    GFX_DRAW_CHAR,
    GFX_DRAW_TEXT,
    GFX_PUT_CHAR,
    GFX_DRAW_RECTANGLE
};

struct gfx_rectangle {
    int x, y, width, height;
};

#define GFX_TEXT_MAX 100
struct gfx_text {
    int x, y;
    char data[GFX_TEXT_MAX];
    unsigned char color;
};

struct gfx_char {
    int x, y;
    char data;
    unsigned char color;
};

#endif /* __GRAPHICS_H */
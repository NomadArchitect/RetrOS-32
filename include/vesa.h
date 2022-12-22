#ifndef DFA8C135_4052_4480_8A44_09EA9D67997D
#define DFA8C135_4052_4480_8A44_09EA9D67997D

#include <stdint.h>
#include <vbe.h>

#define PIXELS_PER_CHAR 8
#define PIXELS_PER_ICON 16

void vesa_put_char(uint8_t* buffer, unsigned char c, int x, int y, int color);
void vesa_put_icon(uint8_t* buffer, int x, int y);
void vesa_write_str(uint8_t* buffer, int x, int y, const char* data, int color);
void vesa_fill(uint8_t* buffer, unsigned char color);

void vesa_put_pixel(uint8_t* buffer, int x,int y, unsigned char color);

inline void putpixel(uint8_t* buffer, int x,int y, char color) {

    uint8_t* pixel_offset = (uint8_t*) (y * vbe_info->pitch + (x * (vbe_info->bpp/8)) + buffer);
    *pixel_offset = color;
}

inline void vesa_line_horizontal(uint8_t* buffer, int x, int y, int length, int color)
{
    for (int i = x; i < (x+length); i++)
        putpixel(buffer, i, y, color);
}

inline void vesa_line_vertical(uint8_t* buffer, int x, int y, int length, int color)
{
    for (int i = y; i < (y+length); i++)
        putpixel(buffer, x, i, color);
}

inline void vesa_fillrect(uint8_t* buffer, int x, int y, int w, int h, int color) {
    int i, j;
    
    for (j = y; j < (y+h); j++)
        for (i = x; i < (x+w); i++)
            putpixel(buffer, i, j, color);
}

int vesa_printf(uint8_t* buffer, int32_t x, int32_t y, int color, char* fmt, ...);

#endif /* DFA8C135_4052_4480_8A44_09EA9D67997D */

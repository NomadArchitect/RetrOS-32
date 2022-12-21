#include <vesa.h>
#include <vbe.h>
#include <colors.h>
#include <util.h>
#include <font8.h>

struct vbe_mode_info_structure* vbe_info;

uint8_t test_icon16[16][16] = {
    {0x00,0x00,0x92,0x92,0x92,0x92,0x92,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,0x92,0xdb,0xfc,0xdb,0xfc,0xdb,0x92,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x92,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0x92,0x92,0x92,0x92,0x92,0x92,0x00,0x00}
    ,{0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x92,0x00,0x00}
    ,{0x92,0xff,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0x92,0x00,0x00}
    ,{0x92,0xff,0xdb,0xfc,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x00}
    ,{0x92,0xff,0xfc,0xdb,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x00}
    ,{0x92,0xff,0xdb,0xfc,0x92,0x92,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x92,0x00}
    ,{0x92,0xff,0xfc,0xdb,0x92,0x92,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x92,0x00}
    ,{0x92,0xff,0xdb,0xfc,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdb,0x00}
    ,{0x92,0xff,0xfc,0xdb,0x92,0xff,0xff,0xfc,0x80,0xff,0xff,0x03,0xff,0xff,0xdb,0x00}
    ,{0x92,0x92,0x92,0x92,0x92,0xff,0x80,0xe0,0x80,0xff,0x10,0x1f,0x03,0xff,0xdb,0x00}
    ,{0x00,0x00,0x00,0x00,0x92,0xff,0xff,0x80,0xff,0xff,0xff,0x10,0x10,0xff,0xdb,0x00}
    ,{0x00,0x00,0x00,0x00,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdb,0x00}
    ,{0x00,0x00,0x00,0x00,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x00}
    ,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
};

uint8_t cursor[16][16] = {
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,0xff,0xff,0xff,0xff,0xff,0x92,0x92,0x92,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,0xff,0xff,0x92,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,0xff,0x92,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,0x92,0x00,0x00,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x92,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
    ,{0x00,0x00,0x00,0x00,0x00,0x00,0x92,0x92,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
};

uint8_t test_icon32[32][32] = {
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
,{0x00,0x00,0x00,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
,{0x00,0x00,0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x92,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
,{0x00,0x92,0xff,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0x92,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
,{0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x00,0x00,0x00,0x00,0x00,0x00}
,{0x92,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00}
,{0x92,0xff,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0x90,0x00,0x00,0x00,0x00,0x00}
,{0x92,0xff,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0x90,0x00,0x00,0x00,0x00,0x00}
,{0x92,0xff,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0x90,0x00,0x00,0x00,0x00,0x00}
,{0x92,0xff,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0x90,0x00,0x00,0x00,0x00,0x00}
,{0x92,0xff,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92}
,{0x92,0xff,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92}
,{0x92,0xff,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0x92,0xdb,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0xff,0x00,0xff,0x00,0xff,0x00,0xdb,0x92}
,{0x92,0xff,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0x92,0xdb,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0xdb,0x92}
,{0x92,0xff,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92}
,{0x92,0xff,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0x92,0xdb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdb,0x92}
,{0x92,0xff,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0x92,0xdb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdb,0x92}
,{0x92,0xff,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0x92,0xdb,0xff,0xff,0xff,0xff,0xe0,0x80,0xff,0xff,0xff,0x03,0xff,0xff,0xff,0xff,0xff,0x10,0x1c,0xff,0xff,0xff,0xdb,0x92}
,{0x92,0xff,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0x92,0xdb,0xff,0xff,0x80,0xe0,0xfc,0x80,0xff,0xff,0xff,0x1f,0x03,0x03,0xff,0xff,0x10,0x10,0x10,0x1c,0xff,0xff,0xdb,0x92}
,{0x92,0xff,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0x92,0xdb,0xff,0xff,0xdb,0x80,0x80,0xff,0xff,0xff,0x82,0xdb,0x82,0x82,0xff,0xff,0xff,0x1c,0x03,0x03,0xff,0xff,0xdb,0x92}
,{0x92,0xff,0xfc,0xdb,0xfc,0xdb,0xfc,0xdb,0x92,0xdb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdb,0x92}
,{0x92,0xff,0xdb,0xfc,0xdb,0xfc,0xdb,0xfc,0x92,0xdb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdb,0x92}
,{0x92,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x92,0xdb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdb,0x92}
,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x92,0xdb,0xff,0xff,0xff,0x1c,0x03,0xff,0xff,0xff,0xff,0xff,0x03,0xff,0xff,0xff,0x80,0xe0,0xff,0xff,0xff,0xff,0xdb,0x92}
,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x92,0xdb,0xff,0xff,0x1c,0x10,0x03,0x03,0xff,0xff,0x03,0x03,0x1f,0xff,0xff,0xff,0x80,0xfc,0xe3,0xe3,0xff,0xff,0xdb,0x92}
,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x92,0xdb,0xff,0xff,0x03,0x03,0x1c,0xff,0xff,0xff,0x82,0x82,0xdb,0x82,0xff,0xff,0xff,0xe3,0x80,0xdb,0xff,0xff,0xdb,0x92}
,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x92,0xdb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdb,0x92}
,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x92,0xdb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdb,0x92}
,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x92,0xdb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xdb,0x92}
,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x92,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0xdb,0x92}
,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92}
,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
};

uint8_t vesa_icon_color_map[255];


#define VESA_BG_COLOR VESA8_COLOR_DARK_TURQUOISE

/* http://www.piclist.com/tecHREF/datafile/charset/extractor/charset_extractor.html */

unsigned short b8to16(unsigned char c)
{
    return (((unsigned short)c)<<8 ) | c;
}

inline void putpixel(int x,int y, char color) {

    uint8_t* pixel_offset = (uint8_t*) (y * vbe_info->pitch + (x * (vbe_info->bpp/8)) + vbe_info->framebuffer);

    *pixel_offset = color;
}


void vesa_put_pixel(int x,int y, unsigned char color)
{
    putpixel(x , y, color);
}

void vesa_put_char(unsigned char c, int x, int y)
{
    for (int l = 0; l < 8; l++) {
        for (int i = 8; i >= 0; i--) {
            if (font8x8_basic[c][l] & (1 << i)) {
                putpixel((x*PIXELS_PER_CHAR)+i,  (y*PIXELS_PER_CHAR)+l, VGA_COLOR_WHITE);
            } else {
                putpixel((x*PIXELS_PER_CHAR)+i,  (y*PIXELS_PER_CHAR)+l, VESA_BG_COLOR);
            }
        }
    }
}

/*
    Possible icons colors prefix:
    18, 
*/
void vesa_put_icon32(int x, int y)
{
    for (int l = 0; l < 32; l++) {

        for (int i = 0; i < 32; i++) {
            if (test_icon32[l][i] != 0x0) {
                putpixel((x)+i,  (y)+l, vesa_icon_color_map[test_icon32[l][i]]);
            } else {
                putpixel((x)+i,  (y)+l, VESA_BG_COLOR);
            }
        }
    }
}

void vesa_put_icon16(int x, int y)
{
    for (int l = 0; l < 16; l++) {

        for (int i = 0; i < 16; i++) {
            if (cursor[l][i] != 0x0) {
                putpixel((x)+i,  (y)+l, vesa_icon_color_map[cursor[l][i]]);
            } else {
                putpixel((x)+i,  (y)+l, VESA_BG_COLOR);
            }
        }
    }
}

void vesa_write(int x, int y, const char* data, int size)
{
	for (int i = 0; i < size; i++)
		vesa_put_char( data[i], x+i, y);
}

void vesa_write_str(int x, int y, const char* data)
{
	vesa_write(x, y, data, strlen(data));
}

inline void vesa_line_horizontal(int x, int y, int length, int color)
{
    for (int i = x; i < (x+length); i++)
        putpixel(i, y, color);
}

inline void vesa_line_vertical(int x, int y, int length, int color)
{
    for (int i = y; i < (y+length); i++)
        putpixel(x, i, color);
}

void vesa_fillrect(int x, int y, int w, int h, int color) {
    int i, j;
    
    for (j = y; j < (y+h); j++)
        for (i = x; i < (x+w); i++)
            putpixel(i, j, color);
}

void vesa_inner_box(int x, int y, int w, int h)
{
    vesa_fillrect(x, y, w, h, VESA8_COLOR_LIGHT_GRAY3);

    vesa_line_horizontal(x, y, w, VESA8_COLOR_DARK_GRAY2);
    vesa_line_horizontal(x, y+h, w, VESA8_COLOR_LIGHT_GRAY1);

    vesa_line_vertical(x, y, h, VESA8_COLOR_DARK_GRAY2);
    vesa_line_vertical(x+w, y, h, VESA8_COLOR_LIGHT_GRAY1);

}

void vesa_fill(unsigned char color)
{
    for (int i = 0; i < vbe_info->height; i++)
        for (int j = 0; j < vbe_info->width; j++)
            putpixel(j, i, color);


    vesa_fillrect(0, 480-25, 640, 25, VESA8_COLOR_LIGHT_GRAY3);
    vesa_line_horizontal(0, 480-25, 640, VESA8_COLOR_LIGHT_GRAY1);
    vesa_line_horizontal(0, 480-26, 640, VESA8_COLOR_LIGHT_GRAY1);

}

void vesa_background()
{

    char* welcome = "Welcome to VESA! In a glorious 640x480x8 resolution.";
    vesa_write_str(1, 1, welcome);

    vesa_inner_box(638-80, 480-22, 80, 19);
    vesa_put_icon32(10, 10);
}

void vesa_init()
{
    vesa_icon_color_map[0xFF] = VESA8_COLOR_LIGHT_GRAY2;
    vesa_icon_color_map[0x92] = VESA8_COLOR_DARK_GRAY1;
    vesa_icon_color_map[0xdb] = VESA8_COLOR_GRAY1;
    vesa_icon_color_map[0xFC] = 43; // 67
    vesa_icon_color_map[0x02] = 1;

}
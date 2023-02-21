#include <gfx/api.h>
#include <gfx/gfxlib.h>
#include <lib/graphics.h>

int gfx_syscall_hook(int option, void* data)
{
    switch (option)
    {
    case GFX_DRAW_CHAR_OPT:;
        struct gfx_char* c = (struct gfx_char*)data;
        __gfx_draw_char(c->x, c->y, c->data, c->color);
        break;
    case GFX_DRAW_RECTANGLE_OPT:;
        struct gfx_rectangle* r = (struct gfx_rectangle*)data;
        __gfx_draw_rectangle(r->x, r->y, r->width, r->height, r->color);
        break;
    
    case GFX_DRAW_CIRCLE_OPT:;
        struct gfx_circle* circle = (struct gfx_circle*)data;
        __gfx_draw_circle(circle->x, circle->y, circle->r, circle->color);
        break;
    
    case GFX_DRAW_LINE_OPT:;
        struct gfx_line* line = (struct gfx_line*)data;
        __gfx_draw_line(line->x0, line->y0, line->x1, line->y1, line->color);
        break;
    default:
        break;
    }

    gfx_commit();

    return 0;
}
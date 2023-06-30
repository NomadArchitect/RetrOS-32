/**
 * @file gfxlib.c
 * @author Joe Bayer (joexbayer)
 * @brief GFX library for rending to a framebuffer.
 * @version 0.1
 * @date 2023-01-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <gfx/gfxlib.h>
#include <gfx/events.h>
#include <pcb.h>
#include <font8.h>
#include <vbe.h>
#include <args.h>
#include <vbe.h>
#include <serial.h>
#include <scheduler.h>
#include <kutils.h>

int gfx_get_window_width()
{
	return current_running->gfx_window->inner_width;
}

int gfx_get_window_height()
{
	return current_running->gfx_window->inner_height;
}

int gfx_push_event(struct window* w, struct gfx_event* e)
{
	dbgprintf("Pushing event %d (head %d): data %d, data2 %d\n", e->event, w->events.head, e->data, e->data2);

	SPINLOCK(w,  {
		memcpy(&w->events.list[w->events.head], e, sizeof(*e));
		w->events.head = (w->events.head + 1) % GFX_MAX_EVENTS;
	});

	/* TODO: Check for a block reason */
	if(w->owner->state == BLOCKED) w->owner->state = RUNNING;

	return 0;
}

int gfx_event_loop(struct gfx_event* event, gfx_event_flag_t flags)
{
	/**
	 * The gfx event loop is PCB specific,
	 * checks if there is an event if true return.
	 * Else block.
	 */
	while(1){
		if(current_running->gfx_window->events.tail == current_running->gfx_window->events.head){
			
			if(flags & GFX_EVENT_BLOCKING){
				/* FIXME: Should not global block, perhaps window manager block queue? */
				current_running->state = BLOCKED;
				kernel_yield();
			} else {
				return -1;
			}
			continue;
		}

		SPINLOCK(current_running->gfx_window, {
			memcpy(event, &current_running->gfx_window->events.list[current_running->gfx_window->events.tail], sizeof(struct gfx_event));
			current_running->gfx_window->events.tail = (current_running->gfx_window->events.tail + 1) % GFX_MAX_EVENTS;
		});
		return 0;
	}
}

/**
 * @brief Draws a rectangle onto the inner framebufferfor currently running process.
 * 
 * @param x coordinate
 * @param y coordiante
 * @param width of rectangle
 * @param height of rectangle
 * @param color
 * @return int 0 on success, less than 0 on error
 */
int kernel_gfx_draw_rectangle(int x, int y, int width, int height, unsigned char color)
{
	if(current_running->gfx_window == NULL)
		return -1;
	/*  */
	if(x < 0 || y < 0 || x+width > current_running->gfx_window->inner_width || y+height > current_running->gfx_window->inner_height)
		return -2;

	int i, j;
	for (j = y; j < (y+height); j++)
		for (i = x; i < (x+width); i++)
			putpixel(current_running->gfx_window->inner, i, j, color, current_running->gfx_window->pitch);

	return 0;
}
/**
 * @brief Draws a character to the framebuffer of currently running process.
 * 
 * @param x coordinate
 * @param y coordiante
 * @param c character
 * @param color 
 * @return int 0 on success, less than 0 on error.
 */
int kernel_gfx_draw_char(int x, int y, unsigned char c, unsigned char color)
{

	if(current_running->gfx_window == NULL)
		return -1;

	//ENTER_CRITICAL();
	for (int l = 0; l < 8; l++) {
		for (int i = 8; i >= 0; i--) {
			if (font8x8_basic[c][l] & (1 << i)) {

				if((x)+i < 0 || (y)+l < 0 || (x)+i > current_running->gfx_window->inner_width || (y)+l > current_running->gfx_window->inner_height)
					continue;
				putpixel(current_running->gfx_window->inner, (x)+i, (y)+l, color, current_running->gfx_window->pitch);
			}
		}
	}
	//LEAVE_CRITICAL();

	//dbgprintf("[GFX] %s put %c\n", current_running->name, c);
	//current_running->gfx_window->changed = 1;

	return 0;
}

void kernel_gfx_set_position(int x, int y)
{
	current_running->gfx_window->x = x;
	current_running->gfx_window->y = y;
}

void gfx_commit()
{
	current_running->gfx_window->changed = 1;
}

/**
 * @brief kernel_gfx_draw_char wrapper for strings
 * 
 * @param x 
 * @param y 
 * @param str string to write.
 * @param color 
 * @return int 0 on success, less than 0 on error.
 */
int kernel_gfx_draw_text(int x, int y, char* str, unsigned char color)
{
	if(current_running->gfx_window == NULL)
		return -1;

	for (int i = 0; i < strlen(str); i++)
	{
		kernel_gfx_draw_char(x+(i*8), y, str[i], color);
	}

	return 0;
}

int kernel_gfx_set_title(char* title)
{
	if(strlen(title) > GFX_MAX_WINDOW_NAME_SIZE)
		return -1;
	
	memset(current_running->gfx_window->name, 0, GFX_MAX_WINDOW_NAME_SIZE);
	memcpy(current_running->gfx_window->name, title, strlen(title));

	return 0;
}

int kernel_gfx_set_header(const char* header)
{
	if(strlen(header) > GFX_MAX_WINDOW_NAME_SIZE)
		return -1;
	
	memset(current_running->gfx_window->header, 0, GFX_MAX_WINDOW_NAME_SIZE);
	memcpy(current_running->gfx_window->header, header, strlen(header));

	return 0;
}

#define ABS(N) ((N<0)?(-N):(N))

/**
plotLine(x0, y0, x1, y1)
	dx = abs(x1 - x0)
	sx = x0 < x1 ? 1 : -1
	dy = -abs(y1 - y0)
	sy = y0 < y1 ? 1 : -1
	error = dx + dy
	
	while true
		plot(x0, y0)
		if x0 == x1 && y0 == y1 break
		e2 = 2 * error
		if e2 >= dy
			if x0 == x1 break
			error = error + dy
			x0 = x0 + sx
		end if
		if e2 <= dx
			if y0 == y1 break
			error = error + dx
			y0 = y0 + sy
		end if
	end while
*/

void kernel_gfx_draw_line(int x0, int y0, int x1, int y1, unsigned char color)  
{  
	int dx, dy, sx, sy, error;
	int t1 = x1-x0;
	int t2 = y1-y0;
	dx= ABS(t1);
	sx = x0 < x1 ? 1 : -1;
	dy=-(ABS(t2));  
	sy = y0 < y1 ? 1 : -1;

	error = dx + dy;

	while(1)  
	{  
		putpixel(current_running->gfx_window->inner, y0, x0, color, current_running->gfx_window->pitch); 
		if (x0 == x1 && y0 == y1) break;
		int e2 = 2*error;

		if( e2 >= dy){
			if (x0 == x1) break;
			error = error + dy;
			x0 = x0 + sx;
		}

		if( e2 <= dx){
			if (y0 == y1) break;
			error = error + dx;
			y0 = y0 + sy;
		}
	}

	gfx_commit();
}  

void kernel_gfx_draw_circle_helper(int xc, int yc, int x, int y, unsigned char color)
{
	putpixel(current_running->gfx_window->inner, xc+x, yc+y, color, current_running->gfx_window->pitch);
	putpixel(current_running->gfx_window->inner, xc-x, yc+y, color, current_running->gfx_window->pitch);
	putpixel(current_running->gfx_window->inner, xc+x, yc-y, color, current_running->gfx_window->pitch);
	putpixel(current_running->gfx_window->inner, xc-x, yc-y, color, current_running->gfx_window->pitch);
	putpixel(current_running->gfx_window->inner, xc+y, yc+x, color, current_running->gfx_window->pitch);
	putpixel(current_running->gfx_window->inner, xc-y, yc+x, color, current_running->gfx_window->pitch);
	putpixel(current_running->gfx_window->inner, xc+y, yc-x, color, current_running->gfx_window->pitch);
	putpixel(current_running->gfx_window->inner, xc-y, yc-x, color, current_running->gfx_window->pitch);
}
 
// using Bresenham's algorithm
void kernel_gfx_draw_circle(int xc, int yc, int r, unsigned char color)
{
	int x = 0, y = r;
	int d = 3 - 2 * r;
	kernel_gfx_draw_circle_helper(xc, yc, x, y, color);
	while (y >= x)
	{
		// for each pixel we will
		// draw all eight pixels
		 
		x++;
 
		// check for decision parameter
		// and correspondingly
		// update d, x, y
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;
		kernel_gfx_draw_circle_helper(xc, yc, x, y, color);
	}

	gfx_commit();
}


#define GFX_MAX_FMT 50
int kernel_gfx_draw_format_text(int x, int y, unsigned char color, char* fmt, ...)
{
	va_list args;

	int x_offset = 0;
	int written = 0;
	char str[GFX_MAX_FMT];
	int num = 0;

	va_start(args, fmt);

	while (*fmt != '\0') {
		switch (*fmt)
		{
			case '%':
				memset(str, 0, GFX_MAX_FMT);
				switch (*(fmt+1))
				{
					case 'd':
					case 'i': ;
						num = va_arg(args, int);
						itoa(num, str);
						kernel_gfx_draw_text(x+(x_offset*PIXELS_PER_CHAR), y, str, color);
						x_offset += strlen(str);
						break;
					case 'p': ; /* p for padded int */
						num = va_arg(args, int);
						itoa(num, str);

						if(strlen(str) < 6){
							int pad = 6-strlen(str);
							for (int i = 0; i < pad; i++){
								kernel_gfx_draw_char(x+(x_offset*PIXELS_PER_CHAR), y,'0', color);
								x_offset++;
							}
						}
								dbgprintf("OFFSET %d\n", strlen(str));

						kernel_gfx_draw_text(x+(x_offset*PIXELS_PER_CHAR), y, str, color);
						x_offset += strlen(str);
						break;
					case 'x':
					case 'X': ;
						num = va_arg(args, int);
						itohex(num, str);
						kernel_gfx_draw_text(x+(x_offset*PIXELS_PER_CHAR), y, str, color);
						x_offset += strlen(str);
						break;
					case 's': ;
						char* str_arg = va_arg(args, char *);
						kernel_gfx_draw_text(x+(x_offset*PIXELS_PER_CHAR), y, str_arg, color);
						x_offset += strlen(str_arg);
						break;
					case 'c': ;
						char char_arg = (char)va_arg(args, int);
						kernel_gfx_draw_char(x+(x_offset*PIXELS_PER_CHAR), y, char_arg, color);
						x_offset++;
						break;
					default:
						break;
				}
				fmt++;
				break;
			case '\n':
				y++;
				written += x_offset;
				x_offset = 0;
				break;
			default:  
				kernel_gfx_draw_char(x+(x_offset*PIXELS_PER_CHAR), y, *fmt, color);
				x_offset++;
				written++;
			}
		fmt++;
	}
	written += x_offset;
	return written;
}
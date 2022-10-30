#ifndef _IZGRAPHICS
#define _IZGRAPHICS

#include<stdint.h>
#include <linux/fb.h>


typedef struct point
{
    int x;
    int y;
} point;

typedef struct screen
{
    struct fb_fix_screeninfo finfo;
	struct fb_var_screeninfo vinfo;
    uint8_t *frame_buffer;
    long screensize;
    int frame_buffer_file;
}screen;


void get_screen(screen *);

void close_screen(screen *);

void draw_line(point, point,uint32_t,screen *);

uint32_t pixel_color(uint8_t, uint8_t, uint8_t, screen *);

#endif /* IZGRAPHICS */
#ifndef _IZGRAPHICS
#define _IZGRAPHICS

#include<stdint.h>
#include <linux/fb.h>


typedef struct point2d
{
    int x;
    int y;
} point2d;

typedef struct screen
{
    struct fb_fix_screeninfo finfo; // fixed framebuffer info
	struct fb_var_screeninfo vinfo; // varying framebuffer info
    uint8_t *frame_buffer; // pointer to the framebuffer memory
    long screensize;
    int frame_buffer_file; // file descriptor of frame buffer
}screen;


void get_screen(screen *);

void close_screen(screen *);

void draw_line(point2d, point2d,uint32_t,screen *);

void clear(screen *);

uint32_t pixel_color(uint8_t, uint8_t, uint8_t, screen *);

#endif /* IZGRAPHICS */
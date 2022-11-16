/* iz-graphics.c - library to open linux framebuffer and draw to it */

/* 1 includes */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <sys/mman.h>
#include<unistd.h>
#include <errno.h>

#include"iz-graphics.h"

static inline void put_pixel(point2d, uint32_t,screen *);
int diagonal_distance(point2d, point2d);


void get_screen( screen *screen){
    // open framebuffer service
    int fb_fd = open("/dev/fb0",O_RDWR);

    setegid(getgid());

    if (fb_fd == -1){
        perror(0);
        exit(1);
    }

    //Get variable screen information
	ioctl(fb_fd, FBIOGET_VSCREENINFO, &(screen->vinfo));
    //Get fixed screen information
    ioctl(fb_fd, FBIOGET_FSCREENINFO, &(screen->finfo));

    screen->frame_buffer_file = fb_fd;

    screen->screensize = screen->vinfo.yres_virtual * screen->finfo.line_length;

    // map the framebuffer in memory
    screen->frame_buffer = mmap(0, screen->screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, (off_t)0);
}

static inline void put_pixel(point2d coord, uint32_t color,screen *screen){
    // testing if the pixel is correctly in the bond of the screen
    if (coord.x >=0 && coord.y >=0 && coord.x < (screen->vinfo.xres) && coord.y < (screen->vinfo.yres)){
        // compute location in memory corresponding to the pixel
        long location = (coord.x+(screen->vinfo.xoffset)) * (screen->vinfo.bits_per_pixel/8) + (coord.y+(screen->vinfo.yoffset)) * (screen->finfo.line_length);
        // putting the color in the pixel
        *((uint32_t*)(screen->frame_buffer + location)) = color;
    }
    else {
        //printf("error writing out of the bond of the frame buffer");
        //exit(0);
    }
    
}

int diagonal_distance(point2d p1, point2d p2){
    int d1 = abs(p1.x - p2.x);
    int d2 = abs(p1.y - p2.y);
    return (d1>=d2)?d1:d2;
}

void draw_line(point2d pt1, point2d pt2,uint32_t color,screen *screen){
    // regular line drawing algorithm
    int nb = diagonal_distance(pt1,pt2);
    float dx = (pt1.x - pt2.x)/(float)nb;
    float dy = (pt1.y - pt2.y)/(float)nb;
    float x = pt2.x;
    float y = pt2.y;
    point2d interpolated_point;
    for (int i = 0;i<nb+1;i++){
	interpolated_point.x = (int) x;
	interpolated_point.y = (int) y;
        put_pixel(interpolated_point,color,screen);
        x += dx;
        y += dy;
    }
}

void clear(screen *screen){
    // put the color black on each pixel of the screen
    point2d point;
    for (point.x = 0;point.x<screen->vinfo.xres;point.x++){
        for (point.y= 0; point.y < screen->vinfo.yres; point.y++)
        {
            put_pixel(point,0,screen);
        }
        
    }
}

uint32_t pixel_color(uint8_t r, uint8_t g, uint8_t b, screen *screen)
{
	return (r<<(screen->vinfo.red.offset)) | (g<<(screen->vinfo.green.offset)) | (b<<(screen->vinfo.blue.offset));
}

void close_screen(screen * screen){
    // close file descriptor of the frame buffer
    close(screen->frame_buffer_file);
}

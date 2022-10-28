#include<stdio.h>
#include<stdlib.h>

#include<stdint.h>
#include<sys/mman.h>
#include<sys/ioctl.h>
#include<unistd.h>

#include <linux/fb.h>
#include <fcntl.h>
#include <errno.h>

void perror(const char *s);

typedef struct point
{
    int x;
    int y;
} point;

static inline void put_pixel(point coord, uint32_t color,struct fb_var_screeninfo *vinfo,struct fb_fix_screeninfo *finfo,uint8_t *fbp){
    if (coord.x >=0 && coord.y >=0 && coord.x<vinfo->xres && coord.y<vinfo->yres){
        long location = (coord.x+vinfo->xoffset) * (vinfo->bits_per_pixel/8) + (coord.y+vinfo->yoffset) * finfo->line_length;
        *((uint32_t*)(fbp + location)) = color;
    }
    else {
        printf("error writing out of the bond of the frame buffer");
        exit(0);
    }
    
}
int diagonal_distance(point p1, point p2){
    int d1 = abs(p1.x - p2.x);
    int d2 = abs(p1.y - p2.y);
    return (d1>=d2)?d1:d2;
}

static inline void draw_line(point pt1, point pt2,uint32_t color,struct fb_var_screeninfo *vinfo,struct fb_fix_screeninfo *finfo,uint8_t *fbp){
    int nb = diagonal_distance(pt1,pt2);
    float dx = (pt1.x - pt2.x)/(float)nb;
    float dy = (pt1.y - pt2.y)/(float)nb;
    float x = pt2.x;
    float y = pt2.y;
    point interpolated_point;
    for (int i = 0;i<nb+1;i++){
	interpolated_point.x = (int) x;
	interpolated_point.y = (int) y;
        put_pixel(interpolated_point,color,vinfo,finfo,fbp);
        x += dx;
        y += dy;
    }
}


static inline uint32_t pixel_color(uint8_t r, uint8_t g, uint8_t b, struct fb_var_screeninfo *vinfo)
{
	return (r<<vinfo->red.offset) | (g<<vinfo->green.offset) | (b<<vinfo->blue.offset);
}


int main(){

    struct fb_fix_screeninfo finfo;
	struct fb_var_screeninfo vinfo;
    
    int fb_fd = open("/dev/fb0",O_RDWR);

    setegid(getgid());


    if (fb_fd == -1){
        perror(0);
        exit(1);
    }

    //Get variable screen information
	ioctl(fb_fd, FBIOGET_VSCREENINFO, &vinfo);
    //Get fixed screen information
    ioctl(fb_fd, FBIOGET_FSCREENINFO, &finfo);

    long screensize = vinfo.yres_virtual * finfo.line_length;

    uint8_t *fbp = mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, (off_t)0);

    int x,y;

    uint32_t blue = pixel_color(0x00,0x00,0xFF, &vinfo);
    uint32_t red = pixel_color(0xFF,0x00,0x00, &vinfo);
    uint32_t green = pixel_color(0x00,0xFF,0x00, &vinfo);


    while (1){
	uint32_t color = pixel_color((uint8_t) rand(),(uint8_t) rand(),(uint8_t) rand(),&vinfo); 
    	point rnd_point_1;
    	rnd_point_1.x = (int)(rand()* ((vinfo.xres-1)/(float)RAND_MAX));
    	rnd_point_1.y = (int)(rand()* ((vinfo.yres-1)/(float)RAND_MAX));

    	point rnd_point_2;
    	rnd_point_2.x = (int)(rand()* ((vinfo.xres-1)/(float)RAND_MAX));
    	rnd_point_2.y = (int)(rand()* ((vinfo.yres-1)/(float)RAND_MAX));
    	//printf("%d\n",rnd_point.x);
    	//printf("%d\n",rnd_point.y);

    	//put_pixel(rnd_point,blue,&vinfo,&finfo,fbp);
    	draw_line(rnd_point_1,rnd_point_2,color,&vinfo,&finfo,fbp);
	sleep(1);
    }
    close(fb_fd);

    return EXIT_SUCCESS;
}

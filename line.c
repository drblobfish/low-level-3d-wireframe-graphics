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

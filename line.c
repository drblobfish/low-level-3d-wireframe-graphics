#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<stdint.h>

#include"iz-graphics.h"


void line(screen * screen){
    uint32_t blue = pixel_color(0x00,0x00,0xFF, screen);
    uint32_t red = pixel_color(0xFF,0x00,0x00, screen);
    uint32_t green = pixel_color(0x00,0xFF,0x00, screen);


    while (1){
	uint32_t color = pixel_color((uint8_t) rand(),(uint8_t) rand(),(uint8_t) rand(),screen); 
    	point2d rnd_point_1;
    	rnd_point_1.x = (int)(rand()* ((screen->vinfo.xres-1)/(float)RAND_MAX));
    	rnd_point_1.y = (int)(rand()* ((screen->vinfo.yres-1)/(float)RAND_MAX));

    	point2d rnd_point_2;
    	rnd_point_2.x = (int)(rand()* ((screen->vinfo.xres-1)/(float)RAND_MAX));
    	rnd_point_2.y = (int)(rand()* ((screen->vinfo.yres-1)/(float)RAND_MAX));
    	//printf("%d\n",rnd_point.x);
    	//printf("%d\n",rnd_point.y);

    	//put_pixel(rnd_point,blue,&vinfo,&finfo,fbp);
    	draw_line(rnd_point_1,rnd_point_2,color,screen);
	sleep(1);
    }
}
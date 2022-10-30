/* 3d wireframe, a program that shows wireframe graphics of meshes*/

/* 1 includes */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "iz-graphics.h"

/* 2 defines */
/* 3 external declarations */
/* 4 typedefs */
/* 5 global variable declarations */
/* 6 function prototypes */

int main(int argc, char *argv[]) {
    /* 7 command-line parsing */

    screen screen;

    get_screen(&screen);
    int x,y;

    uint32_t blue = pixel_color(0x00,0x00,0xFF, &screen);
    uint32_t red = pixel_color(0xFF,0x00,0x00, &screen);
    uint32_t green = pixel_color(0x00,0xFF,0x00, &screen);


    while (1){
	uint32_t color = pixel_color((uint8_t) rand(),(uint8_t) rand(),(uint8_t) rand(),&screen); 
    	point rnd_point_1;
    	rnd_point_1.x = (int)(rand()* ((screen.vinfo.xres-1)/(float)RAND_MAX));
    	rnd_point_1.y = (int)(rand()* ((screen.vinfo.yres-1)/(float)RAND_MAX));

    	point rnd_point_2;
    	rnd_point_2.x = (int)(rand()* ((screen.vinfo.xres-1)/(float)RAND_MAX));
    	rnd_point_2.y = (int)(rand()* ((screen.vinfo.yres-1)/(float)RAND_MAX));
    	//printf("%d\n",rnd_point.x);
    	//printf("%d\n",rnd_point.y);

    	//put_pixel(rnd_point,blue,&vinfo,&finfo,fbp);
    	draw_line(rnd_point_1,rnd_point_2,color,&screen);
	sleep(1);
    }

    close_screen(&screen);

    return EXIT_SUCCESS;
}

/* 8 function declarations */
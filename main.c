/* 3d wireframe, a program that shows wireframe graphics of meshes*/

/* 1 includes */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "iz-graphics.h"
#include "line.h"
#include "3d_mesh.h"

/* 2 defines */
/* 3 external declarations */
/* 4 typedefs */
/* 5 global variable declarations */
/* 6 function prototypes */

int main(int argc, char *argv[]) {
    /* 7 command-line parsing */

    screen screen;

    get_screen(&screen);

	camera camera = {
        {0,0,0},
        {1,0,0},
        {0,1,0},
        {0,0,1},
        1,
        1
    };

    uint32_t blue = pixel_color(0x00,0x00,0xFF, &screen);

    point3d point1 = {3,1,1};
    point3d point2= {3,-1,1};
    point3d point3= {4,-1,1};
    point3d point4= {4,1,1};

    point2d point1_screen= project_point(point1,camera,&screen);
    point2d point2_screen= project_point(point2,camera,&screen);
    point2d point3_screen= project_point(point3,camera,&screen);
    point2d point4_screen= project_point(point4,camera,&screen);

    draw_line(point1_screen,point2_screen,blue,&screen);
    draw_line(point2_screen,point3_screen,blue,&screen);
    draw_line(point3_screen,point4_screen,blue,&screen);
    draw_line(point4_screen,point1_screen,blue,&screen);


    close_screen(&screen);

    return EXIT_SUCCESS;
}

/* 8 function declarations */
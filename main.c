/* 3d wireframe, a program that shows wireframe graphics of meshes*/

/* 1 includes */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "iz-graphics.h"
#include "line.h"
#include "3d_mesh.h"
#include "parse_polygon.h"

/* 2 defines */
/* 3 external declarations */
/* 4 typedefs */
/* 5 global variable declarations */
/* 6 function prototypes */

void print_cube(camera camera,screen * screen){
    uint32_t blue = pixel_color(0x00,0x00,0xFF, screen);

    point3d point1 = {3,1,1};
    point3d point2= {3,-1,1};
    point3d point3= {4,-1,1};
    point3d point4= {4,1,1};

    point3d point5 = {3,1,-1};
    point3d point6= {3,-1,-1};
    point3d point7= {4,-1,-1};
    point3d point8= {4,1,-1};

    point2d point1_screen= project_point(point1,camera,screen);
    point2d point2_screen= project_point(point2,camera,screen);
    point2d point3_screen= project_point(point3,camera,screen);
    point2d point4_screen= project_point(point4,camera,screen);

    point2d point5_screen= project_point(point5,camera,screen);
    point2d point6_screen= project_point(point6,camera,screen);
    point2d point7_screen= project_point(point7,camera,screen);
    point2d point8_screen= project_point(point8,camera,screen);

    draw_line(point1_screen,point2_screen,blue,screen);
    draw_line(point2_screen,point3_screen,blue,screen);
    draw_line(point3_screen,point4_screen,blue,screen);
    draw_line(point4_screen,point1_screen,blue,screen);

    draw_line(point8_screen,point5_screen,blue,screen);
    draw_line(point5_screen,point6_screen,blue,screen);
    draw_line(point6_screen,point7_screen,blue,screen);
    draw_line(point7_screen,point8_screen,blue,screen);

    draw_line(point1_screen,point5_screen,blue,screen);
    draw_line(point2_screen,point6_screen,blue,screen);
    draw_line(point3_screen,point7_screen,blue,screen);
    draw_line(point4_screen,point8_screen,blue,screen);
}

int main(int argc, char *argv[]) {
    /* 7 command-line parsing */

    if (argc==1){
        perror("Please provide a 3d mesh");
        exit(EXIT_FAILURE);
    }

    FILE *fp;
    fp = fopen(argv[1], "r"); // read mode

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    screen screen;

    get_screen(&screen);

	camera camera = {
        {-3.2,1.1,1.3},
        {1,0,0},
        {0,1,0},
        {0,0,1},
        8,
        4
    };

    //camera camera = parse_camera();

    //print_cube(camera,&screen);

    polyhedron my_polygon = parse_polygon(fp);

    draw_polyhedron(&my_polygon,camera,&screen);

    free_polyhedron(&my_polygon);

    fclose(fp);

    close_screen(&screen);

    return EXIT_SUCCESS;
}

/* 8 function declarations */

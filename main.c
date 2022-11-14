/* 3d wireframe, a program that shows wireframe graphics of meshes*/

/* 1 includes */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

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

    struct termios attr;
    
    tcgetattr(0, &attr);
    attr.c_lflag &= ~ICANON;
    attr.c_lflag &= ~ECHO;
    cc_t backup_VMIN = attr.c_cc[VMIN];
    cc_t backup_VTIME = attr.c_cc[VTIME];
    attr.c_cc[VMIN] = 1;
    attr.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &attr);


    screen screen;

    get_screen(&screen);

	camera camera = {
        {-5,0,0},
        
        {0,0,0},

        8,
        4
    };

    //print_cube(camera,&screen);

    polyhedron my_polygon = parse_polygon(fp);

    int input_char;

    while (1)
    {
        input_char = getchar();
        switch (input_char)
        {
        case 'z':
            camera.position.y +=1;
            break;
        case 's':
            camera.position.y -=1;
            break;
        case 'q':
            camera.position.z +=1;
            break;
        case 'd':
            camera.position.z -=1;
            break;
        case 'a':
            camera.position.x +=1;
            break;
        case 'e':
            camera.position.x -=1;
            break;
        case 'j':
            camera.euler_angle.alpha -=0.1;
            break;     
        case 'l':
            camera.euler_angle.alpha +=0.1;
            break;
        case 'i':
            camera.euler_angle.beta +=0.1;
            break;
        case 'k':
            camera.euler_angle.beta -=0.1;
            break;
        case 'u':
            camera.euler_angle.gamma +=0.1;
            break;
        case 'o':
            camera.euler_angle.gamma -=0.1;
            break;
        default:
            break;
        }

        clear(&screen);

        draw_polyhedron(&my_polygon,camera,&screen);
    }

    attr.c_lflag &= ICANON;
    attr.c_lflag &= ECHO;
    attr.c_cc[VMIN] = backup_VMIN;
    attr.c_cc[VTIME] = backup_VTIME;
    tcsetattr(0, TCSANOW, &attr);

    free_polyhedron(&my_polygon);

    fclose(fp);

    close_screen(&screen);

    return EXIT_SUCCESS;
}

/* 8 function declarations */

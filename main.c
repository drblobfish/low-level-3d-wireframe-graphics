/* 3d wireframe, a program that shows wireframe graphics of meshes*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#include "iz-graphics.h"
#include "3d_mesh.h"
#include "parse_polygon.h"


int main(int argc, char *argv[]) {
    /* Opening the polygon file */

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

    /* Terminal setup */

    struct termios attr;
    
    tcgetattr(0, &attr);
    attr.c_lflag &= ~ICANON;
    attr.c_lflag &= ~ECHO;
    cc_t backup_VMIN = attr.c_cc[VMIN];
    cc_t backup_VTIME = attr.c_cc[VTIME];
    attr.c_cc[VMIN] = 1;
    attr.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &attr);

    /* setup iz-graphics */
    screen screen;
    get_screen(&screen);

    /* setup camera at location (-5,0,0) and facing forward */

	camera camera;
    camera.position.x = -5;
    camera.position.y = 0;
    camera.position.z = 0;

    euler_angle base_orientation = {0,0,0};

    camera.orientation = euler_to_orientation(base_orientation);

    camera.fov_x = 8;
    camera.fov_y = 4;


    /* parsing polygon file */
    polyhedron my_polygon = parse_polygon(fp);

    /* generate rotation matrix for each roation buttons*/
    base_rotation base_rotation = generate_base_roation(0.1);

    /* get the key pressed */
    int input_char;
    while (1)
    {
        input_char = getchar();
        switch (input_char)
        {
        case 'z':
            camera.position = add_point3d(camera.position,camera.orientation.normal);
            break;
        case 's':
            camera.position = sub_point3d(camera.position,camera.orientation.normal);
            break;
        case 'd':
            camera.position = add_point3d(camera.position,camera.orientation.horizontal);
            break;
        case 'q':
            camera.position = sub_point3d(camera.position,camera.orientation.horizontal);
            break;
        case 'a':
            camera.position = add_point3d(camera.position,camera.orientation.vertical);
            break;
        case 'e':
            camera.position = sub_point3d(camera.position,camera.orientation.vertical);
            break;
        case 'j':
            camera.orientation = mult_orient(camera.orientation,base_rotation.gamma_forw);
            break;     
        case 'l':
            camera.orientation = mult_orient(camera.orientation,base_rotation.gamma_backw);
            break;
        case 'i':
            camera.orientation = mult_orient(camera.orientation,base_rotation.alpha_forw);
            break;
        case 'k':
            camera.orientation = mult_orient(camera.orientation,base_rotation.alpha_backw);
            break;
        case 'u':
            camera.orientation = mult_orient(camera.orientation,base_rotation.beta_forw);
            break;
        case 'o':
            camera.orientation = mult_orient(camera.orientation,base_rotation.beta_backw);
            break;
        default:
            break;
        }
        /* clear screen */
        clear(&screen);

        printf("\033[%d;%dH%f %f %f\n", 4, 4,camera.position.x,camera.position.y,camera.position.z);

        /* draw polygon */
        draw_polyhedron(&my_polygon,camera,&screen);
    }

    /* close file revert terminal configuration and free memory */
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

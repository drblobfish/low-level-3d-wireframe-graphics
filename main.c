/* 3d wireframe, a program that shows wireframe graphics of meshes*/

/* 1 includes */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "iz-graphics.h"
#include "line.h"

/* 2 defines */
/* 3 external declarations */
/* 4 typedefs */
/* 5 global variable declarations */
/* 6 function prototypes */

int main(int argc, char *argv[]) {
    /* 7 command-line parsing */

    screen screen;

    get_screen(&screen);

	line(&screen);

    close_screen(&screen);

    return EXIT_SUCCESS;
}

/* 8 function declarations */
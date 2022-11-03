#ifndef _3D_POINT
#define _3D_POINT

#include "iz-graphics.h"


typedef struct point3d
{
    float x;
    float y;
    float z;
} point3d;

typedef struct camera
{
    point3d position;
    point3d normal;
    point3d vertical;
    point3d horizontal;
    float fov_x;
    float fov_y;
}camera;

point2d project_point(point3d,camera,screen *screen);


#endif	/* _3D_POINT */
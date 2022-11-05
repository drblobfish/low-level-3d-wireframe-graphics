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

typedef struct edge
{
    point3d *point1;
    point3d *point2;
}edge;

typedef struct polyhedron
{
    int nb_node;
    int nb_edge;
    point3d *nodes;
    edge *edges;
    
}polyhedron;

void free_polyhedron(polyhedron*);

void draw_polyhedron(polyhedron*,camera,screen *);

point2d project_point(point3d,camera,screen *);



#endif	/* _3D_POINT */
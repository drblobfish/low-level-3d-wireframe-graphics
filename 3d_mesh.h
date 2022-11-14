#ifndef _3D_POINT
#define _3D_POINT

#include "iz-graphics.h"


typedef struct point3d
{
    float x;
    float y;
    float z;
} point3d;

typedef struct euler_angle
{
    float alpha;
    float beta;
    float gamma;
} euler_angle;


typedef struct orientation
{
    point3d normal;
    point3d vertical;
    point3d horizontal;
} orientation;

typedef struct camera
{
    point3d position;
    orientation orientation;
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

typedef struct base_rotation
{
    orientation alpha_forw;
    orientation alpha_backw;

    orientation beta_forw;
    orientation beta_backw;

    orientation gamma_forw;
    orientation gamma_backw;
}base_rotation;

point3d add_point3d(point3d, point3d);

point3d sub_point3d(point3d, point3d);

base_rotation generate_base_roation(float);

orientation mult_orient(orientation,orientation);

orientation euler_to_orientation(euler_angle);

void free_polyhedron(polyhedron*);

void draw_polyhedron(polyhedron*,camera,screen *);

point2d project_point(point3d,camera,screen *);



#endif	/* _3D_POINT */
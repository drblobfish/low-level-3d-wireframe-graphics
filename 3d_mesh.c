#include <stdio.h>
#include <stdlib.h>

#include "3d_mesh.h"

point3d add_point3d(point3d point1, point3d point2)
{
    point1.x += point2.x;
    point1.y += point2.y;
    point1.z += point2.z;

    return point1;
}

point3d sub_point3d(point3d point1, point3d point2)
{
    point1.x -= point2.x;
    point1.y -= point2.y;
    point1.z -= point2.z;

    return point1;
}

static inline float dot_product(point3d point1, point3d point2)
{
    return point1.x * point2.x + point1.y * point2.y + point1.z * point2.z;
}

point2d project_point(point3d _point3d, camera camera, screen *screen)
{

    _point3d = sub_point3d(_point3d, camera.position);

    point3d point_camera_space;

    point_camera_space.x = dot_product(_point3d, camera.horizontal);
    point_camera_space.y = dot_product(_point3d, camera.vertical);
    point_camera_space.z = dot_product(_point3d, camera.normal);

    point2d point_screen_space;

    point_screen_space.x = (int)(point_camera_space.x * (screen->vinfo.xres) / (point_camera_space.z * camera.fov_x));
    point_screen_space.y = (int)(point_camera_space.y * (screen->vinfo.yres) / (point_camera_space.z * camera.fov_y));

    point_screen_space.x += screen->vinfo.xres / 2;
    point_screen_space.y += screen->vinfo.yres / 2;

    return point_screen_space;
}

void draw_polyhedron(polyhedron *polyhedron_, camera camera, screen *screen)
{
    uint32_t white = pixel_color(0xFF, 0xFF, 0xFF, screen);

    for (int i = 0; i < polyhedron_->nb_edge; i++)
    {
        edge edge = polyhedron_->edges[i];
        point2d point1 = project_point(*(edge.point1), camera, screen);
        point2d point2 = project_point(*(edge.point2), camera, screen);
        draw_line(point1, point2, white, screen);
    }
}

void free_polyhedron(polyhedron *polygon)
{
    free(polygon->edges);
    free(polygon->nodes);
}

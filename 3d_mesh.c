#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

orientation euler_to_orientation(euler_angle euler_angle){
    orientation orientation;
    float c1 = cosf(euler_angle.alpha),c2 = cosf(euler_angle.beta), c3 = cosf(euler_angle.gamma),
            s1 = sinf(euler_angle.alpha),s2 = sinf(euler_angle.beta), s3 = sinf(euler_angle.gamma);

    orientation.normal.x = c1 * c3 - c2 * s1 * s3;
    orientation.normal.y = c3 * s1 + c1 * c2 * s3;
    orientation.normal.z = s2 * s3;

    orientation.vertical.x = - c1 * s3 - c2 * c3 * s1;
    orientation.vertical.y = c1 * c2 * c3 - s1 * s3;
    orientation.vertical.z = c3 * s2;

    orientation.horizontal.x = s1 * s2;
    orientation.horizontal.y = - c1 * s2;
    orientation.horizontal.z = c2;

    return orientation;

}

point2d project_point(point3d _point3d, camera camera, screen *screen)
{

    _point3d = sub_point3d(_point3d, camera.position);

    orientation orientation = euler_to_orientation(camera.euler_angle);

    point3d point_camera_space;

    point_camera_space.x = dot_product(_point3d, orientation.horizontal);
    point_camera_space.y = dot_product(_point3d, orientation.vertical);
    point_camera_space.z = dot_product(_point3d, orientation.normal);

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

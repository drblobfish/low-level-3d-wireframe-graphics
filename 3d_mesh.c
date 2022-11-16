#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "3d_mesh.h"

point3d add_point3d(point3d point1, point3d point2)
{
    // vector addition
    point1.x += point2.x;
    point1.y += point2.y;
    point1.z += point2.z;

    return point1;
}

point3d sub_point3d(point3d point1, point3d point2)
{
    // substract vector point 2 to point 1
    point1.x -= point2.x;
    point1.y -= point2.y;
    point1.z -= point2.z;

    return point1;
}

orientation mult_orient(orientation or1,orientation rot){
    // matrix multiplication rot*or1
    orientation or_res;
    or_res.normal.x = or1.normal.x * rot.normal.x + or1.normal.y * rot.vertical.x + or1.normal.z * rot.horizontal.x;
    or_res.normal.y = or1.normal.x * rot.normal.y + or1.normal.y * rot.vertical.y + or1.normal.z * rot.horizontal.y;
    or_res.normal.z = or1.normal.x * rot.normal.z + or1.normal.y * rot.vertical.z + or1.normal.z * rot.horizontal.z;

    or_res.vertical.x = or1.vertical.x * rot.normal.x + or1.vertical.y * rot.vertical.x + or1.vertical.z * rot.horizontal.x;
    or_res.vertical.y = or1.vertical.x * rot.normal.y + or1.vertical.y * rot.vertical.y + or1.vertical.z * rot.horizontal.y;
    or_res.vertical.z = or1.vertical.x * rot.normal.z + or1.vertical.y * rot.vertical.z + or1.vertical.z * rot.horizontal.z;

    or_res.horizontal.x = or1.horizontal.x * rot.normal.x + or1.horizontal.y * rot.vertical.x + or1.horizontal.z * rot.horizontal.x;
    or_res.horizontal.y = or1.horizontal.x * rot.normal.y + or1.horizontal.y * rot.vertical.y + or1.horizontal.z * rot.horizontal.y;
    or_res.horizontal.z = or1.horizontal.x * rot.normal.z + or1.horizontal.y * rot.vertical.z + or1.horizontal.z * rot.horizontal.z;

    return or_res;
}

static inline float dot_product(point3d point1, point3d point2)
{
    // dot product
    return point1.x * point2.x + point1.y * point2.y + point1.z * point2.z;
}

base_rotation generate_base_roation(float step){
    /* generate 6 roation matrix, 3 being the inverse from the 3 others
    each matrix correspond to a rotation of step radian around one of the 
    canonical vectors 
    They are used for keyboard control, because there are 6 keys that each 
    cause a rotation of the camera around one axis*/

    float sin = sinf(step);
    float cos = cosf(step);

    base_rotation base_rotation;

    base_rotation.alpha_forw.normal.x = cos;
    base_rotation.alpha_forw.normal.y = sin;
    base_rotation.alpha_forw.normal.z = 0;
    base_rotation.alpha_forw.vertical.x = -sin;
    base_rotation.alpha_forw.vertical.y = cos;
    base_rotation.alpha_forw.vertical.z = 0;
    base_rotation.alpha_forw.horizontal.x = 0;
    base_rotation.alpha_forw.horizontal.y = 0;
    base_rotation.alpha_forw.horizontal.z = 1;

    base_rotation.alpha_backw.normal.x = cos;
    base_rotation.alpha_backw.normal.y = -sin;
    base_rotation.alpha_backw.normal.z = 0;
    base_rotation.alpha_backw.vertical.x = sin;
    base_rotation.alpha_backw.vertical.y = cos;
    base_rotation.alpha_backw.vertical.z = 0;
    base_rotation.alpha_backw.horizontal.x = 0;
    base_rotation.alpha_backw.horizontal.y = 0;
    base_rotation.alpha_backw.horizontal.z = 1;

    base_rotation.beta_forw.normal.x = 1;
    base_rotation.beta_forw.normal.y = 0;
    base_rotation.beta_forw.normal.z = 0;
    base_rotation.beta_forw.vertical.x = 0;
    base_rotation.beta_forw.vertical.y = cos;
    base_rotation.beta_forw.vertical.z = sin;
    base_rotation.beta_forw.horizontal.x = 0;
    base_rotation.beta_forw.horizontal.y = -sin;
    base_rotation.beta_forw.horizontal.z = cos;

    base_rotation.beta_backw.normal.x = 1;
    base_rotation.beta_backw.normal.y = 0;
    base_rotation.beta_backw.normal.z = 0;
    base_rotation.beta_backw.vertical.x = 0;
    base_rotation.beta_backw.vertical.y = cos;
    base_rotation.beta_backw.vertical.z = -sin;
    base_rotation.beta_backw.horizontal.x = 0;
    base_rotation.beta_backw.horizontal.y = sin;
    base_rotation.beta_backw.horizontal.z = cos;

    base_rotation.gamma_forw.normal.x = cos;
    base_rotation.gamma_forw.normal.y = 0;
    base_rotation.gamma_forw.normal.z = sin;
    base_rotation.gamma_forw.vertical.x = 0;
    base_rotation.gamma_forw.vertical.y = 1;
    base_rotation.gamma_forw.vertical.z = 0;
    base_rotation.gamma_forw.horizontal.x = -sin;
    base_rotation.gamma_forw.horizontal.y = 0;
    base_rotation.gamma_forw.horizontal.z = cos;

    base_rotation.gamma_backw.normal.x = cos;
    base_rotation.gamma_backw.normal.y = 0;
    base_rotation.gamma_backw.normal.z = -sin;
    base_rotation.gamma_backw.vertical.x = 0;
    base_rotation.gamma_backw.vertical.y = 1;
    base_rotation.gamma_backw.vertical.z = 0;
    base_rotation.gamma_backw.horizontal.x = sin;
    base_rotation.gamma_backw.horizontal.y = 0;
    base_rotation.gamma_backw.horizontal.z = cos;

    return base_rotation;
}


orientation euler_to_orientation(euler_angle euler_angle){
    /* converts euler angle to a rotation matrix
    see https://en.wikipedia.org/wiki/Euler_angles#Rotation_matrix
    after some testing, I'm still unsure if it works correctly */
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
    /* takes a point in 3d space and a camera and return the position 
    in screen space of point */

    /* place the camera at the origin */
    _point3d = sub_point3d(_point3d, camera.position);


    /* expresses the position of the point in the basis of the camera
    because the 3 vectors that encode the orientation of the camera 
    form an *orthonormal* basis, this change of basis is achieved 
    by computing the dot product of the point with each vector */
    point3d point_camera_space;
    point_camera_space.x = dot_product(_point3d, camera.orientation.horizontal);
    point_camera_space.y = dot_product(_point3d, camera.orientation.vertical);
    point_camera_space.z = dot_product(_point3d, camera.orientation.normal);

    /* the projection in itself (just dividing x and y by z (the distance to the camera)) */
    point2d point_screen_space;
    point_screen_space.x = (int)(point_camera_space.x * (screen->vinfo.xres) / (point_camera_space.z * camera.fov_x));
    point_screen_space.y = (int)(point_camera_space.y * (screen->vinfo.yres) / (point_camera_space.z * camera.fov_y));

    /* placing the focus point of the camera on the middle of the screen */
    point_screen_space.x += screen->vinfo.xres / 2;
    point_screen_space.y += screen->vinfo.yres / 2;

    return point_screen_space;
}

void draw_polyhedron(polyhedron *polyhedron_, camera camera, screen *screen)
{   
    /* a polygon is a graph whose nodes are 3d points 
    This function iterates over all edges, projects the two points
    associated with the edge and display a line between the two point 
    in screen space */
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
    /* free the dynamically allocated polygon data */
    free(polygon->edges);
    free(polygon->nodes);
}

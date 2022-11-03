#include<stdio.h>
#include<stdlib.h>

#include "3d_mesh.h"

point3d add_point3d(point3d point1,point3d point2){
    point1.x += point2.x;
    point1.y += point2.y;
    point1.z += point2.z;

    return point1;
}

point3d sub_point3d(point3d point1,point3d point2){
    point1.x -= point2.x;
    point1.y -= point2.y;
    point1.z -= point2.z;

    return point1;
}

point2d project_point(point3d point3d, camera camera){

    point3d = sub_point3d(point3d,camera.position);

}
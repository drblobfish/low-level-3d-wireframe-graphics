#include <stdio.h>
#include <stdlib.h>
#include "3d_mesh.h"

polyhedron parse_polygon(){
    polyhedron polygon;
    scanf("%d\n",&polygon.nb_node);
    scanf("%d\n",&polygon.nb_edge);

    polygon.nodes = (point3d *) calloc(polygon.nb_node,sizeof(point3d));
    polygon.edges = (edge *) calloc(polygon.nb_edge,sizeof(edge));

    scanf("\n");

    for (int i = 0; i < polygon.nb_node; i++)
    {
        scanf("%f %f %f\n",&(polygon.nodes[i].x),&(polygon.nodes[i].y),&(polygon.nodes[i].z));
    }
    scanf("\n");

    for (int i = 0; i < polygon.nb_edge; i++)
    {
        int index1,index2;
	if (index1>=polygon.nb_node || index2>=polygon.nb_node ||
	    index1<0 || index2<0){
	    printf("invalid polygon file");
	    exit(0);
	}
        scanf("%d %d",&index1,&index2);
        polygon.edges[i].point1 = &(polygon.nodes[index1]);
        polygon.edges[i].point2 = &(polygon.nodes[index2]);
    }

    return polygon;  
}

camera parse_camera(){
    camera camera;
    scanf("%f %f %f\n",&(camera.position.x),&(camera.position.y),&(camera.position.z));

    scanf("%f %f %f\n",&(camera.normal.x),&(camera.normal.y),&(camera.normal.z));
    scanf("%f %f %f\n",&(camera.vertical.x),&(camera.vertical.y),&(camera.vertical.z));
    scanf("%f %f %f\n",&(camera.horizontal.x),&(camera.horizontal.y),&(camera.horizontal.z));

    scanf("%f\n",&camera.fov_x);
    scanf("%f\n",&camera.fov_y);

    return camera;

}

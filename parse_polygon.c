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
        scanf("%f %f %f\n",&(polygon.nodes[i].x),&(polygon.nodes[i].y),&(polygon.nodes[i].y));
    }
    scanf("\n");

    for (int i = 0; i < polygon.nb_edge; i++)
    {
        int index1,index2;
        scanf("%d %d",&index1,&index2);
        polygon.edges[i].point1 = &(polygon.nodes[index1]);
        polygon.edges[i].point2 = &(polygon.nodes[index2]);
    }

    return polygon;  
}
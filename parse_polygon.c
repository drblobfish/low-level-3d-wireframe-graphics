#include <stdio.h>
#include <stdlib.h>
#include "3d_mesh.h"

polyhedron parse_polygon(FILE *polygon_file){
    polyhedron polygon;
    fscanf(polygon_file,"%d\n",&polygon.nb_node);
    fscanf(polygon_file,"%d\n",&polygon.nb_edge);

    polygon.nodes = (point3d *) calloc(polygon.nb_node,sizeof(point3d));
    polygon.edges = (edge *) calloc(polygon.nb_edge,sizeof(edge));

    fscanf(polygon_file,"\n");

    for (int i = 0; i < polygon.nb_node; i++)
    {
        fscanf(polygon_file,"%f %f %f\n",&(polygon.nodes[i].x),&(polygon.nodes[i].y),&(polygon.nodes[i].z));
    }
    fscanf(polygon_file,"\n");

    for (int i = 0; i < polygon.nb_edge; i++)
    {
        int index1,index2;
	
        fscanf(polygon_file,"%d %d",&index1,&index2);

        if (index1>=polygon.nb_node || index2>=polygon.nb_node ||
            index1<0 || index2<0){
            printf("invalid polygon file %d %d\n",index1,index2);
            exit(0);
        }
        polygon.edges[i].point1 = &(polygon.nodes[index1]);
        polygon.edges[i].point2 = &(polygon.nodes[index2]);
    }

    return polygon;  
}

#include "stats.h"
#include "search.h"

int numberOfEdges(char name[]){
    FILE *fp;
    int src, dest, weight;
    int edge_num = 0, vertex_num = 0;
    graph_l *graph = (graph_l *)malloc(sizeof(graph_l));
    fp = fopen(name, "r");

    while (fscanf(fp, "%d %d %d", &src, &dest, &weight) != EOF){
        edge_num++;
    }
    return edge_num;
}

int numberOfVertices(char name[]){
    FILE *fp;
    int src, dest, weight;
    int edge_num = 0, vertex_num = 0;
    graph_l *graph = (graph_l *)malloc(sizeof(graph_l));
    fp = fopen(name, "r");

    while (fscanf(fp, "%d %d %d", &src, &dest, &weight) != EOF){
        if (src + 1 > vertex_num){
            vertex_num = src + 1;
        }
    }
    return vertex_num;
}
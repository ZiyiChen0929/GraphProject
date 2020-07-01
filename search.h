#ifndef SEARCHCLI_SEARCH_H
#define SEARCHCLI_SEARCH_H
#include <stdio.h>
#include <stdlib.h>

typedef struct adj_matrix {
    int vertex_n;
    int   edge_n;
    int **matrix;
}graph_m;

typedef struct adj_node {
    int               val;
    int       edge_weight;
    struct adj_node *next;
}edge_t;

typedef struct vertex {
    int             val;
    edge_t *next;
}vertex_t;

typedef struct adj_list {
    int   vertex_n;
    int     edge_n;
    vertex_t **list;
}graph_l;

graph_l *read_graph_info(char *filp);
void bfs(graph_l *graph);
void dfs(graph_l *graph);

#endif //SEARCHCLI_SEARCH_H

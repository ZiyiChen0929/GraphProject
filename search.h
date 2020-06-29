#ifndef SEARCH-CLI_UTIL_H
#define SEARCH-CLI_UTIL_H
#include <stdio.h>
#include <stdlib.h>

typedef struct adj_matrix {
    int vertex_n;
    int   edge_n;
    int **matrix;
}graph_m;

typedef struct vertex {
    int             val;
    struct vertex *next;
}vertex_t;

typedef struct adj_node {
    int               val;
    int       edge_weight;
    struct adj_node *next;
}node_t;

typedef struct adj_list {
    int   vertex_n;
    int     edge_n;
    vertex_t *list;
}graph_l;

void graph_m_init(FILE *fp);
void graph_l_init(FILE *fp);
void bfs(graph_l *graph);
void dfs(graph_l *graph);

#endif //SEARCH-CLI_UTIL_H

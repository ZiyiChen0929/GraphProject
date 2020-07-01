#include "search.h"

graph_l *read_graph_info(char *filp) {
    FILE *fp;
    int src, dest, weight;
    int edge_num = 0, vertex_num = 0;
    graph_l *graph = (graph_l *)malloc(sizeof(graph_l));
    fp = fopen(filp, "r");

    while (fscanf(fp, "%d %d %d", &src, &dest, &weight) != EOF){
        edge_num++;
        if (src + 1 > vertex_num){
            vertex_num = src + 1;
        }
    }
    rewind(fp);
    graph->edge_n = edge_num;
    graph->vertex_n = vertex_num;
    graph->list = (vertex_t **)malloc(sizeof(vertex_t *) * (vertex_num + 1));
    for (int i = 1; i <= vertex_num; i++) {
        graph->list[i] = NULL;
    }
    while (fscanf(fp, "%d %d %d", &src, &dest, &weight) != EOF){
        if (graph->list[src] == NULL){
            vertex_t *new_vtx = (vertex_t *)malloc(sizeof(vertex_t));
            new_vtx->val = src;
            new_vtx->next = NULL;
            graph->list[src] = new_vtx;
        }
        edge_t *new_eg = (edge_t *)malloc(sizeof(edge_t));
        new_eg->val = dest;
        new_eg->edge_weight = weight;
        new_eg->next = graph->list[src]->next;
        graph->list[src]->next = new_eg;
    }
    return graph;
}

void bfs(graph_l *graph) {
    printf("This is bfs\n");
}

void dfs(graph_l *graph) {
    printf("This is dfs\n");
}

void dijkstra(graph_l *graph){
    printf("This is dijkstra\n");
}



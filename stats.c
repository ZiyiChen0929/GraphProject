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

double freemanNetworkCentrality(char name[]){
    graph_l *graph_e = read_graph_info(name);
    int degree[graph_e->vertex_n + 1];
    int max = -1;
    for (int i = 1; i <= graph_e->vertex_n; i++) {
        degree[i] = 0;
    }
    for (int j = 1; j <= graph_e->vertex_n; j++) {
        if (graph_e->list[j] == NULL){
            degree[j] = 0;
        }
        else {
            edge_t *edge_e = graph_e->list[j]->next;
            while (edge_e != NULL){
                degree[j]++;
                degree[edge_e->val]++;
                edge_e = edge_e->next;
            }
        }
    }
    for (int k = 1; k <= graph_e->vertex_n; k++) {
        if (degree[k] > max){
            max = degree[k];
        }
    }
    double weight_sum = 0;
    for (int l = 1; l <= graph_e->vertex_n; l++) {
        weight_sum += (max - degree[l]);
    }
    return weight_sum / (graph_e->vertex_n - 1) * (graph_e->vertex_n - 2);
}
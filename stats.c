#include "stats.h"
#include "search.h"

int numberOfEdges(char name[]){
    FILE *fp;
    int src, dest, weight;
    int edge_num = 0;
    fp = fopen(name, "r");

    while (fscanf(fp, "%d %d %d", &src, &dest, &weight) != EOF){
        edge_num++;
    }
    return edge_num;
}

int numberOfVertices(char name[]){
    FILE *fp;
    int ret = 0;
    int src, dest, weight;
    int vertex_num = 0;
    int *mark;
    fp = fopen(name, "r");

    while (fscanf(fp, "%d %d %d", &src, &dest, &weight) != EOF){
        int tmp = src > dest ? src : dest;
        if (tmp + 1 > vertex_num){
            vertex_num = tmp + 1;
        }
    }
    mark = (int *)malloc(sizeof(int) * vertex_num);
    for (int i = 0; i < vertex_num; i++) {
        mark[i] = 0;
    }
    rewind(fp);
    while (fscanf(fp, "%d %d %d", &src, &dest, &weight) != EOF){
        mark[src] += 1;
        mark[dest] += 1;
    }

    for (int i = 0; i < vertex_num; i++) {
        if (mark[i] != 0){
            ret++;
        }
    }
    return ret;
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
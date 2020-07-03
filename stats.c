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

float freemanNetworkCentrality(char name[]){
    FILE *fp;
    int src, dest, weight;
    int edge_num = 0, vertex_num = 0;
    graph_l *graph_e = (graph_l *)malloc(sizeof(graph_l));
    fp = fopen(name, "r");

    while (fscanf(fp, "%d %d %d", &src, &dest, &weight) != EOF){
        edge_num++;
        int tmp = src > dest ? src : dest;
        if (tmp + 1 > vertex_num){
            vertex_num = tmp + 1;
        }
    }
    rewind(fp);
    graph_e->edge_n = edge_num;
    graph_e->vertex_n = vertex_num;
    /* adjacency list */
    graph_e->list = (vertex_t **)malloc(sizeof(vertex_t *) * (vertex_num + 1));
    for (int i = 0; i <= vertex_num; i++) {
        graph_e->list[i] = NULL;
    }
    while (fscanf(fp, "%d %d %d", &src, &dest, &weight) != EOF){
        int flag = 0;
        if (graph_e->list[src] != NULL && graph_e->list[dest] != NULL){
            edge_t *scan = graph_e->list[src]->next;
            while (scan != NULL){
                if (scan->val == dest){
                    flag = 1;
                    break;
                }
                scan = scan->next;
            }
            if (flag == 1){
                continue;
            }
            scan = graph_e->list[dest]->next;
            while (scan != NULL){
                if (scan->val == src){
                    flag = 1;
                    break;
                }
                scan = scan->next;
            }
            if (flag == 1){
                continue;
            }
        }
        else {
            if (graph_e->list[src] == NULL){
                vertex_t *new_vtx_src = (vertex_t *)malloc(sizeof(vertex_t));
                new_vtx_src->val = src;
                new_vtx_src->next = NULL;
                graph_e->list[src] = new_vtx_src;
            }
            if (graph_e->list[dest] == NULL){
                vertex_t *new_vtx_dest = (vertex_t *)malloc(sizeof(vertex_t));
                new_vtx_dest->val = src;
                new_vtx_dest->next = NULL;
                graph_e->list[dest] = new_vtx_dest;
            }
        }
        edge_t *new_eg = (edge_t *)malloc(sizeof(edge_t));
        new_eg->val = dest;
        new_eg->edge_weight = weight;
        new_eg->next = graph_e->list[src]->next;
        graph_e->list[src]->next = new_eg;
    }

    int degree[graph_e->vertex_n + 1];
    int max = -1;

    for (int i = 0; i <= graph_e->vertex_n; i++) {
        degree[i] = -1;
    }

    for (int j = 0; j <= graph_e->vertex_n; j++) {
        if (graph_e->list[j] == NULL) {
            continue;
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

    for (int k = 0; k <= graph_e->vertex_n; k++) {
        if (degree[k] > max){
            max = degree[k];
        }
    }
    float weight_sum = 0;
    for (int l = 0; l <= graph_e->vertex_n; l++) {
        if (degree[l] == -1){
            continue;
        }
        weight_sum += (max - degree[l]);
    }
    int num_of_vertex = numberOfVertices(name);
    return weight_sum / ((num_of_vertex - 1) * (num_of_vertex - 2));
}
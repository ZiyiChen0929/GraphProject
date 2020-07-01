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

void vec_init(vector_t *vector){
    vector = (vector_t *)malloc(sizeof(vector));
    vector->head = (node_t *)malloc(sizeof(node_t));
    vector->tail = (node_t *)malloc(sizeof(node_t));
    vector->head = NULL;
    vector->tail = NULL;
    vector->len = 0;
}

void append(vector_t *vector, int elem){
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    new_node->vertex = elem;
    vector->tail->next = new_node;
    vector->tail = vector->tail->next;
    vector->len++;
}

int pop(vector_t *vector){
    if (vector->len == 0){
        printf("The vector is empty\n");
        return -1;
    }
    vector->len--;
    if (vector->len == 0){
        node_t *tmp = vector->head;
        int ret = tmp->vertex;
        free(tmp);
        vector->head = NULL;
        vector->tail = NULL;
        return ret;
    }
    node_t *tmp = vector->head;
    while (tmp->next != vector->tail){
        tmp = tmp->next;
    }
    vector->tail = tmp;
    int ret = tmp->next->vertex;
    free(tmp->next);
    return ret;
}

int shift(vector_t *vector){
    if (vector->len == 0){
        printf("The vector is empty\n");
        return -1;
    }
    vector->len--;
    if (vector->len == 0){
        node_t *tmp = vector->head;
        int ret = tmp->vertex;
        free(tmp);
        vector->head = NULL;
        vector->tail = NULL;
        return ret;
    }
    int ret = vector->head->vertex;
    node_t *tmp = vector->head;
    vector->head = vector->head->next;
    free(tmp);
    return ret;
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



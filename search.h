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
    int      val;
    edge_t *next;
}vertex_t;

typedef struct adj_list {
    int   vertex_n;
    int     edge_n;
    vertex_t **list;
}graph_l;

typedef struct node{
    int vertex;
    struct node *next;
}node_t;

typedef struct vector {
    node_t *head;
    node_t *tail;
    int len;
}vector_t;

int my_strlen(char *str);
int my_strcmp(char *str1, char *str2);
int my_strcpy(char *dest, int length, char *src);
char *int_2_string(int number);

void vec_init(vector_t *vector);
void append(vector_t *vector, int elem);
int pop(vector_t *vector);
int shift(vector_t *vector);

graph_l *read_graph_info(char *filp);
void bfs(graph_l *graph);
char *dfs(graph_l *graph, int u, int v);

char *shortestpath(int u, int v, char algorithm[], char name[]);
#endif //SEARCHCLI_SEARCH_H

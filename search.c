#include "search.h"

void swap(hnode_t **x, hnode_t **y) {
    hnode_t *temp = *x;
    *x = *y;
    *y = temp;
}

int my_strlen(char *str) {
    int ret = 0;
    while (str[ret] != '\0'){
        ret++;
    }
    return ret;
}

int my_strcmp(char *str1, char *str2) {
    int len1 = my_strlen(str1);
    int len2 = my_strlen(str2);
    if (len1 != len2) {
        return 0;
    }
    else{
        for (int i = 0; i < len1; i++) {
            if (str1[i] != str2[i]){
                return 0;
            }
        }
        return 1;
    }
}

int my_strcpy(char *dest, int length, char *src){
    if (dest == NULL){
        dest = (char *)malloc(sizeof(char) * (length + 1));
    }
    if (length > my_strlen(src)){
        printf("String length error!\n");
    }
    for (int i = 0; i < length; i++) {
        dest[i] = src[i];
    }
    dest[length] = '\0';
}

char *int_2_string(int number){
    int num = number;
    int index = 0;
    int size = 1;
    char *ret = (char *)malloc(1);
    while (num != 0){
        int digit = num % 10;
        ret = realloc(ret, size + 1);
        ret[index++] = (char)(digit + '0');
        num /= 10;
    }
    ret[index] = '\0';
    return ret;
}

int str_2_int(char *str) {
    char *string = str;
    int ret = 0;
    int len = my_strlen(str);
    for (int i = len - 1; i >= 0; i--) {
        int sum = (int)(string[i] - '0');
        for (int j = 0; j < len - i - 1; ++j) {
            sum *= 10;
        }
        ret += sum;
    }
    return ret;
}

graph_l *read_graph_info(char *filp) {
    FILE *fp;
    int src, dest, weight;
    int edge_num = 0, vertex_num = 0;
    graph_l *graph = (graph_l *)malloc(sizeof(graph_l));
    fp = fopen(filp, "r");

    while (fscanf(fp, "%d %d %d", &src, &dest, &weight) != EOF){
        edge_num++;
        int tmp = src > dest ? src : dest;
        if (tmp + 1 > vertex_num){
            vertex_num = tmp + 1;
        }
    }
    rewind(fp);
    graph->edge_n = edge_num;
    graph->vertex_n = vertex_num;
    /* adjacency list */
    graph->list = (vertex_t **)malloc(sizeof(vertex_t *) * (vertex_num + 1));
    for (int i = 0; i <= vertex_num; i++) {
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

graph_l *expand_graph(char *filp) {
    FILE *fp;
    int src, dest, weight;
    int max_weight = -1;
    int edge_num = 0, vertex_num = 0;
    graph_l *graph = (graph_l *)malloc(sizeof(graph_l));
    fp = fopen(filp, "r");

    while (fscanf(fp, "%d %d %d", &src, &dest, &weight) != EOF){
        if (weight > max_weight){
            max_weight = weight;
        }

        edge_num++;
        int tmp = src > dest ? src : dest;
        if (tmp + 1 > vertex_num){
            vertex_num = tmp + 1;
        }
    }
    rewind(fp);
    graph->edge_n = edge_num;
    graph->v_num = vertex_num;
    /* capacity for all the nodes */
    graph->vertex_n = vertex_num * max_weight;
    /* adjacency list */
    graph->list = (vertex_t **)malloc(sizeof(vertex_t *) * (graph->vertex_n + 1));
    for (int i = 0; i <= graph->vertex_n; i++) {
        graph->list[i] = NULL;
    }
    while (fscanf(fp, "%d %d %d", &src, &dest, &weight) != EOF){
        int i;
        if (graph->list[src] == NULL){
            vertex_t *new_vtx = (vertex_t *)malloc(sizeof(vertex_t));
            new_vtx->val = src;
            new_vtx->next = NULL;
            graph->list[src] = new_vtx;
        }
        for (i = 1; i < weight; i++) {
            edge_t *new_eg = (edge_t *)malloc(sizeof(edge_t));
            new_eg->val = src + i * vertex_num;
            new_eg->edge_weight = 1;
            new_eg->next = graph->list[src + (i - 1) * vertex_num]->next;
            graph->list[src + (i - 1) * vertex_num]->next = new_eg;

            if (graph->list[src + i * vertex_num] == NULL){
                vertex_t *new_vtx = (vertex_t *)malloc(sizeof(vertex_t));
                new_vtx->val = src + i * vertex_num;
                new_vtx->next = NULL;
                graph->list[src + i * vertex_num] = new_vtx;
            }
        }
        edge_t *new_eg = (edge_t *)malloc(sizeof(edge_t));
        new_eg->val = dest;
        new_eg->edge_weight = 1;
        new_eg->next = graph->list[src + (i - 1) * vertex_num]->next;
        graph->list[src + (i - 1) * vertex_num]->next = new_eg;
    }
    return graph;
}

void vec_init(vector_t *vector){
    vector->head = (node_t *)malloc(sizeof(node_t));
    vector->tail = (node_t *)malloc(sizeof(node_t));
    vector->head = NULL;
    vector->tail = NULL;
    vector->len = 0;
}

void append(vector_t *vector, int elem){
    if (vector->head == NULL && vector->tail == NULL){
        node_t *new_node = (node_t*)malloc(sizeof(node_t));
        new_node->vertex = elem;
        new_node->next = NULL;
        vector->tail = new_node;
        vector->head = new_node;
        vector->len++;
        return;
    }
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    new_node->vertex = elem;
    new_node->next = NULL;
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

/* reference from Geeksforgeeks */
void heap_init(heap_t *heap, hnode_t *root){
    heap->heap_size = 0;
    heap->capacity = 100000;
    heap->arr = (hnode_t **)malloc(sizeof(hnode_t *) * heap->capacity);
//    root->weight = 0;
    heap->arr[0] = root;
    heap->heap_size++;
}

void heapify(heap_t *heap, int index){
    int l = left_child(index);
    int r = right_child(index);
    int smallest = index;
    if (l < heap->heap_size && heap->arr[l] < heap->arr[index])
        smallest = l;
    if (r < heap->heap_size && heap->arr[r] < heap->arr[smallest])
        smallest = r;
    if (smallest != index)
    {
        swap(&heap->arr[index], &heap->arr[smallest]);
        heapify(heap, smallest);
    }
}

int parent(int index){
    return (index - 1) / 2;
}

int left_child(int index){
    return 2 * index + 1;
}

int right_child(int index){
    return 2 * index + 2;
}

hnode_t *extract_min(heap_t *heap){
    if (heap->heap_size == 0){
        printf("The heap is empty\n");
        return NULL;
    }
    if (heap->heap_size == 1){
        heap->heap_size--;
        return heap->arr[0];
    }
    hnode_t *root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->heap_size - 1];
    heap->heap_size--;
    heapify(heap, 0);
    return root;
}

hnode_t *get_min(heap_t *heap){
    return heap->arr[0];
}

void insert(heap_t *heap, hnode_t *node){
    if (heap->heap_size == heap->capacity) {
        heap->arr = realloc(heap->arr, ++heap->heap_size);
    }

    heap->heap_size++;
    int i = heap->heap_size - 1;
    heap->arr[i] = node;

    while (i != 0 && heap->arr[parent(i)] > heap->arr[i]) {
        swap(&heap->arr[i], &heap->arr[parent(i)]);
        i = parent(i);
    }
}
/* src: https://www.geeksforgeeks.org/binary-heap/ */

char *copypath(vector_t *vector) {
    char *ret = (char *)malloc(1);
    int index = 0;
    int size = 1;
    node_t *tmp = vector->head;
    while (tmp != NULL) {
        if (tmp->vertex > 9) {
            char *s = int_2_string(tmp->vertex);
            int len = my_strlen(s);
            for (int i = len - 1; i >= 0; i--) {
                ret = realloc(ret, ++size);
                ret[index++] = s[i];
            }
            if (tmp->next != NULL) {
                size += 2;
                ret = realloc(ret, size);
                ret[index++] = '-';
                ret[index++] = '>';
            }
            else {
                ret[index] = '\0';
            }
        }
        else {
            ret = realloc(ret, ++size);
            ret[index++] = (char)(tmp->vertex + '0');
            if (tmp->next != NULL){
                size += 2;
                ret = realloc(ret, size);
                ret[index++] = '-';
                ret[index++] = '>';
            }
            else {
                ret[index] = '\0';
            }
        }
        tmp = tmp->next;
    }
    return ret;
}

char *bfs(graph_l *graph, int u, int v) {
    // Mark all the vertices as not visited
    int *visited = (int *)malloc(sizeof(int) * graph->vertex_n);
    int *parent = (int *)malloc(sizeof(int) * graph->vertex_n);

    for (int i = 0; i < graph->vertex_n; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }

    vector_t *vec = (vector_t *)malloc((sizeof(vector_t)));
    vec_init(vec);

    visited[u] = 1;
    append(vec, u);

    while (vec->len != 0) {
        int s = vec->head->vertex;

        if (s == v) {
            char *path;
            vector_t *p = (vector_t *)malloc(sizeof(vector_t));
            vec_init(p);
            int prev = v;
            append(p, prev);
            while (parent[prev] != -1) {
                prev = parent[prev];
                if (prev > graph->v_num){
                    continue;
                }
                node_t *new_node = (node_t *)malloc(sizeof(node_t));
                new_node->vertex = prev;
                new_node->next = p->head;
                p->head = new_node;
            }
            path = copypath(p);
            return path;
        }

        int head = shift(vec);

        if (graph->list[head] == NULL){
            continue;
        }
        edge_t *scan = graph->list[head]->next;
        while (scan != NULL) {
            if (!visited[scan->val])
            {
                visited[scan->val] = 1;
                append(vec, scan->val);
                parent[scan->val] = s;
            }
            scan = scan->next;
        }
    }
}

char *dfs(graph_l *graph, int u, int v) {
    char *path;
    int visited[graph->vertex_n + 1];
    int ptrlist[graph->vertex_n + 1];
    for (int i = 0; i <= graph->vertex_n; i++) {
        visited[i] = 0;
        ptrlist[i] = 0;
    }

    vector_t *vector;
    vector = (vector_t *)malloc(sizeof(vector_t));
    vec_init(vector);
    append(vector, u);
    visited[u] = 1;

    int flag = 0;
    int pre = u; /* present vertex */
    int weightsum = 0;
    int minweight = 0x7fffffff;

    while(1) {
        int ptr_index = ptrlist[pre];
        if (graph->list[pre] == NULL) {
            int ver = pop(vector);
            ptrlist[ver] = 0;
            pre = vector->tail->vertex;
            visited[ver] = 0;
            edge_t *tmp = graph->list[pre]->next;
            while (tmp->val != ver) {
                tmp = tmp->next;
            }
            weightsum -= tmp->edge_weight;
            continue;
        }
        edge_t *scan = graph->list[pre]->next;

        for (int i = 0; i < ptr_index; i++) {
            scan = scan->next;
        }

        while (scan != NULL && visited[scan->val] == 1) {
            scan = scan->next;
            ptr_index++;
        }

        if(scan == NULL) {
            int ver = pop(vector);
            if (ver == u) {
                if (flag == 1)
                {
                    return path;
                }
                else {
                    return NULL;
                }
            }
            ptrlist[ver] = 0;
            pre = vector->tail->vertex;
            visited[ver] = 0;
            edge_t *tmp = graph->list[pre]->next;
            while (tmp->val != ver) {
                tmp = tmp->next;
            }
            weightsum -= tmp->edge_weight;
            continue;
        }
        else {
            ptrlist[vector->tail->vertex] = ptr_index + 1;
        }

        pre = scan->val;
        append(vector, pre);
        visited[pre] = 1;
        weightsum += scan->edge_weight;

        if (weightsum >= minweight) {
            int ver = pop(vector);
            visited[ver] = 0;
            pre = vector->tail->vertex;
            weightsum -= scan->edge_weight;
            continue;
        }

        if (pre == v) {
            if (weightsum < minweight) {
                minweight = weightsum;
                path = copypath(vector);
                flag = 1;
            }
            int ver = pop(vector);
            visited[ver] = 0;
            pre = vector->tail->vertex;
            weightsum -= scan->edge_weight;
        }
    }
}

char *dijkstra(graph_l *graph, int u, int v) {
    char *path;
    int dist[graph->vertex_n];
    int visited[graph->vertex_n];
    int previous[graph->vertex_n];
    for (int i = 0; i < graph->vertex_n; i++) {
        dist[i] = 0x7fffffff;
        visited[i] = 0;
        previous[i] = -1;
    }
    /* Initialize the priority queue */
    heap_t *pq = (heap_t *)malloc(sizeof(heap_t));
    hnode_t *root = (hnode_t *)malloc(sizeof(hnode_t));
    root->weight = 0;
    root->vertex = u;
    dist[root->vertex] = 0;
    heap_init(pq, root);

    while (get_min(pq)->vertex != v) {
        hnode_t *pre = extract_min(pq);
        if (graph->list[pre->vertex] == NULL){
            continue;
        }
        edge_t *scan = graph->list[pre->vertex]->next;
        while (scan != NULL && visited[scan->val] == 0){
            if (dist[scan->val] > dist[pre->vertex] + scan->edge_weight){
                dist[scan->val] = dist[pre->vertex] + scan->edge_weight;
                hnode_t *new_node = (hnode_t *)malloc(sizeof(hnode_t));
                new_node->vertex = scan->val;
                new_node->weight = dist[scan->val];
                insert(pq, new_node);
                previous[scan->val] = pre->vertex;
            }
            scan = scan->next;
        }
        visited[pre->vertex] = 1;
    }
    vector_t *vec = (vector_t *)malloc(sizeof(vector_t));
    vec_init(vec);
    int parent = v;
    append(vec, parent);
    while (previous[parent] != -1){
        parent = previous[parent];
        node_t *new_node = (node_t *)malloc(sizeof(node_t));
        new_node->vertex = parent;
        new_node->next = vec->head;
        vec->head = new_node;
    }
    path = copypath(vec);
    return path;
}

char *shortestpath(int u, int v, char algorithm[], char name[]){
    graph_l *graph;
    if (my_strcmp(algorithm, "DFS")){
        graph = read_graph_info(name);
        return dfs(graph, u, v);
    }
    else if (my_strcmp(algorithm, "BFS")){
        graph = expand_graph(name);
        return bfs(graph, u, v);
    }
    else if (my_strcmp(algorithm, "Dijkstra")){
        graph = read_graph_info(name);
        return dijkstra(graph, u, v);
    }
    else{
        printf("Algorithm not valid\n");
        return NULL;
    }
}



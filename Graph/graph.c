#include "graph.h"

int add_vertex(Graph* data, char* name, unsigned port){
    data->vertices = realloc(data->vertices, (data->count + 1) * sizeof(Vertex*));

    int result = findVertex(data, name);
    if (result != -1) return 1;

    Vertex* new = calloc(1, sizeof(Vertex));
    new->port = port;
    new->name = name;

    data->vertices[data->count] = new;
    data->count += 1;
    return 0;
}

int add_edge(Graph* data, unsigned int* ports, int size, char* vertex_1, char* vertex_2){
    int pos1 = -1, pos2 = -1;
    pos1 = findVertex(data, vertex_1);
    pos2 = findVertex(data, vertex_2);
    if (pos1 == -1 || pos2 == -1) return 1;
    if (check_overlap(data->vertices[pos1], vertex_2)){
        return 1;
    }
    if (check_overlap(data->vertices[pos2], vertex_1)){
        return 1;
    }

    Edge* edge_1 = make(data->vertices[pos2], ports, size);
    edge_1->next = data->vertices[pos1]->edges;
    data->vertices[pos1]->edges = edge_1;

    unsigned* copy_ports = copy(ports, size);

    Edge* edge_2 = make(data->vertices[pos1], copy_ports, size);
    edge_2->next = data->vertices[pos2]->edges;
    data->vertices[pos2]->edges = edge_2;
    return 0;
}

int change_vertex(Graph* data, char* vertex, char* new_name, unsigned int port){
    int pos = findVertex(data, new_name);
    if (pos != -1) return 1;
    pos = findVertex(data, vertex);
    if (pos == -1) return 1;
    free(data->vertices[pos]->name);
    data->vertices[pos]->name = new_name;
    data->vertices[pos]->port = port;
    return 0;
}

int change_edge(Graph* data, char* vertex1, char* vertex2, int new_size, unsigned int* new_array){
    Edge* e1 = find_edge(data, vertex1, vertex2);
    Edge* e2 = find_edge(data, vertex2, vertex1);
    if (e1 == NULL || e2 == NULL){
        return 1;
    }
    free(e1->ports);
    free(e2->ports);
    e1->size = new_size;
    e2->size = new_size;
    e1->ports = new_array;
    e2->ports = copy(new_array, new_size);

    return 0;
}

int delete_edge(Graph* data, char* vertex1, char* vertex2){
    Edge* e1 = find_edge(data, vertex1, vertex2);
    Edge* e2 = find_edge(data, vertex2, vertex1);
    if (e1 == NULL || e2 == NULL){
        return 1;
    }
    int pos1 = findVertex(data, vertex1);
    int pos2 = findVertex(data, vertex2);
    delete_list(data->vertices[pos1], e1);
    delete_list(data->vertices[pos2], e2);

    return 0;
}

int delete_vertex(Graph* data, char* vertex){
    if (data->count == 0) return 1;
    int pos = findVertex(data, vertex);
    char** ends = NULL;
    int len = 0;

    if (pos == -1) return 1;
    Edge* ptr = data->vertices[pos]->edges;
    Edge* prev = NULL;
    while (ptr){
        len++;
        ends = realloc(ends, len * sizeof(char*));
        ends[len - 1] = ptr->vertex->name;
        prev = ptr;
        ptr = ptr->next;
        free(prev->ports);
        free(prev);
    }
    for (int i = 0; i < len; i++){
        int j = findVertex(data, ends[i]);
        Edge* edge = find_edge(data, data->vertices[j]->name, vertex);
        delete_list(data->vertices[j], edge);
    }

    free(ends);
    free(data->vertices[pos]->name);
    free(data->vertices[pos]);
    data->vertices[pos] = data->vertices[data->count - 1];
    data->vertices = realloc(data->vertices, (data->count - 1) * sizeof(Vertex*));
    data->count -= 1;
    return 0;
}

void free_graph(Graph* data){
    for (int i = 0; i < data->count; i++){
        Edge* ptr = data->vertices[i]->edges;
        Edge* prev = NULL;
        while (ptr){
            prev = ptr;
            ptr = ptr->next;
            free(prev->ports);
            free(prev);
        }
        free(data->vertices[i]->name);
        free(data->vertices[i]);
    }
    free(data->vertices);
    free(data);
}

void DFS(Graph* data, int** visited, char* vertex, unsigned port){
    int pos = findVertex(data, vertex);
    if (data->vertices[pos]->port == port) (*visited)[pos] = 2;
    else (*visited)[pos] = 1;
    Edge* ptr = data->vertices[pos]->edges;
    while (ptr){
        if (in(ptr->ports, ptr->size, port)){
            int p = findVertex(data, ptr->vertex->name);
            if ((*visited)[p] == 0){
                DFS(data, visited, ptr->vertex->name, port);
            }
        }
        ptr = ptr->next;
    }
}

int* Dijkstra(Graph* data, char* vertex){
    int* dist = calloc(data->count, sizeof(int));
    int* visited = calloc(data->count, sizeof(int));
    for (int i = 0; i < data->count; i++){
        dist[i] = INT_MAX - 1;
    }
    int pos = findVertex(data, vertex);
    dist[pos] = 0;
    unsigned port = data->vertices[pos]->port;
    for (int i = 0; i < data->count; i++){
        int min_weight = INT_MAX;
        int min_pos = -1;
        for (int j = 0; j < data->count; j++){
            if (visited[j] == 0 && dist[j] < min_weight){
                min_weight = dist[j];
                min_pos = j;
            }
        }
        for (int j = 0; j < data->count; j++){
            Edge* edge = find_edge(data, data->vertices[min_pos]->name, data->vertices[j]->name);
            if (edge != NULL){
                if (in(edge->ports, edge->size, port)){
                    if (dist[min_pos] + 1 < dist[j]){
                        dist[j] = dist[min_pos] + 1;
                    }
                }
            }
        }
        visited[min_pos] = 1;
    }
    free(visited);
    return dist;
}

Graph* spanning(Graph* data, unsigned port){
    Vertex** connected = calloc(data->count, sizeof(Vertex*));
    Graph* span = calloc(1, sizeof(Graph));
    span->vertices = connected;


    for (int i = 0; i < data->count; i++){
        if (findVertex(span, data->vertices[i]->name) == -1){
            Vertex* new = calloc(1, sizeof(Vertex));
            new->name = strdup(data->vertices[i]->name);
            new->port = data->vertices[i]->port;
            connected[span->count] = new;
            span->count++;
        }
        Edge* ptr = data->vertices[i]->edges;
        while (ptr){
            if (in(ptr->ports, ptr->size, port)){
                int pos1 = findVertex(span, data->vertices[i]->name);
                int pos2 = findVertex(span, ptr->vertex->name);
                if (pos2 == -1){
                    Vertex* new = calloc(1, sizeof(Vertex));
                    new->name = strdup(ptr->vertex->name);
                    new->port = ptr->vertex->port;
                    connected[span->count] = new;
                    span->count++;

                    Edge* edge1 = calloc(1, sizeof(Edge));
                    edge1->ports = copy(ptr->ports, ptr->size);
                    edge1->size = ptr->size;
                    edge1->vertex = span->vertices[span->count - 1];
                    edge1->next = span->vertices[pos1]->edges;
                    span->vertices[pos1]->edges = edge1;

                    Edge* edge2 = calloc(1, sizeof(Edge));
                    edge2->ports = copy(ptr->ports, ptr->size);
                    edge2->size = ptr->size;
                    edge2->vertex = span->vertices[pos1];
                    edge2->next = span->vertices[span->count - 1]->edges;
                    span->vertices[span->count - 1]->edges = edge2;
                }
            }
            ptr = ptr->next;
        }

    }
    return span;
}

int checkIn(Vertex** data, char* vertex, int len){
    for (int i = 0; i < len; i++){
        if (strcmp(data[i]->name, vertex) == 0) return 0;
    }
    return 1;
}

void print(Graph* data){
    for (int i = 0; i < data->count; i++){
        printf("%d: %s(%u)", i + 1, data->vertices[i]->name, data->vertices[i]->port);

        Edge* ptr = data->vertices[i]->edges;
        while (ptr){
            for (int k = 0; k < ptr->size; k++){
                printf("-%u", ptr->ports[k]);
            }
            printf("->%s(%u) |", ptr->vertex->name, ptr->vertex->port);
            ptr = ptr->next;
        }
        printf("\n");
    }
    printf("\n");
}


int findVertex(Graph* data, char* vertex){
    for (int i = 0; i < data->count; i++){
        if (strcmp(data->vertices[i]->name, vertex) == 0){
            return i;
        }
    }
    return -1;
}

static Edge* find_edge(Graph* data, char* vertex1, char* vertex2){
    for (int i = 0; i < data->count; i++){
        if (!strcmp(vertex1, data->vertices[i]->name)){
            Edge* ptr = data->vertices[i]->edges;
            while (ptr){
                if (!strcmp(ptr->vertex->name, vertex2)) return ptr;
                ptr = ptr->next;
            }
            break;
        }
    }
    return NULL;
}

static int check_overlap(Vertex* vertex, char* str){
    Edge* ptr = vertex->edges;
    while (ptr){
        if (strcmp(str, ptr->vertex->name) == 0) return 1;
        ptr = ptr->next;
    }
    return 0;
}

static Edge* make(Vertex* vertex, unsigned int* ports, int size){
    Edge* edge = calloc(1, sizeof(Edge));
    edge->vertex = vertex;
    edge->ports = ports;
    edge->size = size;
    return edge;
}

static unsigned* copy(const unsigned* original, unsigned size){
    unsigned* ports = calloc(size, sizeof(unsigned));
    for (int i = 0; i < size; i++){
        ports[i] = original[i];
    }
    return ports;
}

static void delete_list(Vertex* vertex, Edge* del){
    Edge* ptr = vertex->edges;
    Edge* prev = NULL;
    while (ptr){
        if (ptr == del) break;
        prev = ptr;
        ptr = ptr->next;
    }
    if (del == vertex->edges){
        vertex->edges = del->next;
    }
    else {
        prev->next = del->next;
    }
    free(del->ports);
    free(del);
}

static int in(const unsigned* data, int len, unsigned port){
    for (int i = 0; i < len; i++){
        if (data[i] == port) return 1;
    }
    return 0;
}
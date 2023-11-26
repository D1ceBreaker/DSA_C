#ifndef GRAPH_H
#define GRAPH_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Edge{
    unsigned int* ports;
    int size;
    struct Vertex* vertex;
    struct Edge* next;
}Edge;

typedef struct Vertex{
    unsigned int port;
    char* name;
    Edge* edges;
}Vertex;

typedef struct Graph{
    Vertex** vertices;
    int count;
}Graph;

int add_vertex(Graph* data, char* name, unsigned port);
int add_edge(Graph* data, unsigned int* ports, int size, char* vertex_1, char* vertex_2);
void print(Graph* data);
int delete_vertex(Graph* data, char* vertex);
int delete_edge(Graph* data, char* vertex1, char* vertex2);
void free_graph(Graph* data);
void DFS(Graph* data, int** visited, char* vertex, unsigned port);
int* Dijkstra(Graph* data, char* vertex);
Graph* spanning(Graph* data, unsigned port);

int change_vertex(Graph* data, char* vertex, char* new_name, unsigned int port);
int change_edge(Graph* data, char* vertex1, char* vertex2, int new_size, unsigned int* new_array);

static int check_overlap(Vertex* vertex, char* str);
static Edge* make(Vertex* vertex, unsigned int* ports, int size);

static Edge* find_edge(Graph* data, char* vertex1, char* vertex2);

static void delete_list(Vertex* vertex, Edge* del);

static unsigned* copy(const unsigned* original, unsigned size);
static int in(const unsigned* data, int len, unsigned port);
int findVertex(Graph* data, char* vertex);
int checkIn(Vertex** data, char* vertex, int len);
#endif //GRAPH_H

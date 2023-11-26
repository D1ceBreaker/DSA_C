#include "user.h"

void AddVertex(Graph* data){
    printf("Enter vertex's name:\n");
    scanf("%*c");
    char* name = readline();
    printf("Enter vertex's port:\n");
    unsigned port = getPosInt();

    int result = add_vertex(data, name, port);
    if (result) printf("This vertex already exists\n");
}

void AddEdge(Graph* data){
    printf("Enter the first vertex name:\n");
    scanf("%*c");
    char* name1 = readline();
    printf("Enter the second vertex name:\n");
    char* name2 = readline();
    printf("Enter the number of ports:\n");
    unsigned size = getPosInt();
    printf("Enter the %d ports:\n", size);

    unsigned* ports = getPorts(size);

    int result = add_edge(data, ports, (int) size, name1, name2);
    if (result) printf("This edge already exists\n");
}

void ChangeVertex(Graph* data){
    printf("Enter vertex's name:\n");
    scanf("%*c");
    char* name = readline();
    printf("Enter vertex's new name:\n");
    scanf("%*c");
    char* new = readline();
    printf("Enter vertex's new port:\n");
    unsigned port = getPosInt();

    int result = change_vertex(data, name, new, port);
    if (result) printf("This vertex does not exist\n");
}

void ChangeEdge(Graph* data){
    printf("Enter the first vertex name:\n");
    scanf("%*c");
    char* name1 = readline();
    printf("Enter the second vertex name:\n");
    scanf("%*c");
    char* name2 = readline();
    printf("Enter the number of ports:\n");
    unsigned size = getPosInt();
    printf("Enter the new %d ports:\n", size);

    unsigned* ports = getPorts(size);

    int result = change_edge(data, name1, name2, (int) size, ports);
    if (result) printf("This edge does not exist\n");
}

void DeleteVertex(Graph* data){
    printf("Enter vertex's name:\n");
    scanf("%*c");
    char* name = readline();
    int result = delete_vertex(data, name);
    if (result) printf("This vertex does not exist\n");
}

void DeleteEdge(Graph* data){
    printf("Enter the first vertex name:\n");
    scanf("%*c");
    char* name1 = readline();
    printf("Enter the second vertex name:\n");
    scanf("%*c");
    char* name2 = readline();
    printf("v1: %s\n", name1);
    printf("v2: %s\n", name2);
    int result = delete_edge(data, name1, name2);
    if (result) printf("This edge does not exist\n");
    free(name1);
    free(name2);
}

void DepthSearch(Graph* data){
    printf("Enter vertex's name:\n");
    scanf("%*c");
    char* name = readline();
    printf("Enter vertex's port:\n");
    unsigned port = getPosInt();
    int pos = findVertex(data, name);
    if (pos == -1) return;

    int* visited = calloc(data->count, sizeof(int));
    visited[pos] = 1;
    DFS(data, &visited, name, port);
    for (int i = 0; i < data->count; i++){
        printf("%d - %s\n", visited[i], data->vertices[i]->name);

    }
}

void ShortestPath(Graph* data){
    printf("Enter the first vertex name:\n");
    scanf("%*c");
    char* name1 = readline();
    printf("Enter the second vertex name:\n");
    char* name2 = readline();
    int pos1 = findVertex(data, name1);
    int pos2 = findVertex(data, name2);
    if (pos1 == -1 || pos2 == -1){
        return;
    }
    int* dist = Dijkstra(data, name1);
    if (dist[pos2] == INT_MAX - 1) printf("The path does not exist\n");
    else printf("shortest distance between %s and %s is %d\n", name1, name2, dist[pos2]);
    free(name1);
    free(name2);
    free(dist);
}

Graph* MinSpan(Graph* data){
    printf("Enter vertex's port:\n");
    unsigned port = getPosInt();
    Graph* test = spanning(data, port);
    print(test);
    for (int i = 0; i < test->count; i++){
        printf("v: %s\n", test->vertices[i]->name);
    }
    //free_graph(test);

    return data;
}
static unsigned* getPorts(unsigned len){
    unsigned* ports = calloc(len, sizeof(unsigned));
    for (int i = 0; i < len; i++){
        ports[i] = getPosInt();
    }
    return ports;
}

unsigned int getPosInt(){
    long long int num;
    int k = scanf("%lld", &num);
    while (k <= 0){
        scanf("%*c");
        k = scanf("%lld", &num);
    }
    if (num < 0) num = getPosInt();
    if (num > (long long int) UINT_MAX) num = getPosInt();
    return num;
}

char* readline(){
    //scanf("%*c");
    char* line = calloc(1, sizeof(char));
    int len = 0;
    int c = getchar();
    while (c != '\n'){
        len++;
        line = (char*) realloc(line, (len + 1) * sizeof(char));
        line[len - 1] = (char)c;
        line[len] = '\0';
        c = getchar();
    }
    return line;
}

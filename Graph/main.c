#include <stdio.h>
#include "user.h"
void commands();
void menu();

int main() {
    menu();
    return 0;
}

void menu(){
    printf("%d", INT_MAX);
    commands();
    Graph* data = calloc(1, sizeof(Graph));
    unsigned int option = getPosInt();
    while (option != 11){
        switch (option) {
            case 1:
                AddVertex(data);
                break;
            case 2:
                AddEdge(data);
                break;
            case 3:
                ChangeVertex(data);
                break;
            case 4:
                ChangeEdge(data);
                break;
            case 5:
                DeleteVertex(data);
                break;
            case 6:
                DeleteEdge(data);
                break;
            case 7:
                print(data);
                break;
            case 8:
                DepthSearch(data);
                break;
            case 9:
                ShortestPath(data);
                break;
            case 10:
                data = MinSpan(data);
                break;
            default:
                printf("Unidentified key\n");
                break;
        }
        commands();
        option = getPosInt();

    }

    free_graph(data);
}

void commands(){
    printf("List of options:\n");
    printf("\t1 -> Add a vertex\n");
    printf("\t2 -> Add an edge\n");
    printf("\t3 -> Change a vertex\n");
    printf("\t4 -> Change an edge\n");
    printf("\t5 -> Delete a vertex\n");
    printf("\t6 -> Delete an edge\n");
    printf("\t7 -> Print\n");
    printf("\t8 -> Depth search\n");
    printf("\t9 -> The shortest path\n");
    printf("\t10 -> The least spanning\n");
    printf("\t11 -> Quit\n");
}
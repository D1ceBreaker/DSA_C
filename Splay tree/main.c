#include <stdio.h>
#include "user.h"
#include <string.h>
void commands();
void menu();
int main() {
    Splay* data = calloc(1, sizeof(Splay));
    push(data, strdup("aa"), 1);
    push(data, strdup("cd"), 1);
    ascetic(data, data->root);
    searchMax(data, "b");
    //menu();
    return 0;
}
void menu(){
    commands();
    Splay* data = calloc(1, sizeof(Splay));
    unsigned int option = getPosInt();
    while (option != 7){
        switch (option) {
            case 1:
                Add(data);
                break;
            case 2:
                Delete(data);
                break;
            case 3:
                Find(data);
                break;
            case 4:
                SpecialFind(data);
                break;
            case 5:
                if (data->root){
                    ascetic(data, data->root);
                }
                else printf("Tree is empty\n");
                break;
            case 6:
                Upload(data);
                break;
            default:
                printf("Unidentified key\n");
                break;
        }
        commands();
        option = getPosInt();

    }
    free_tree(data->root);
    free(data);
}

void commands(){
    printf("List of options:\n");
    printf("\t1 -> Add an element\n");
    printf("\t2 -> Delete key\n");
    printf("\t3 -> Find key\n");
    printf("\t4 -> Find the minimum\n");
    printf("\t5 -> Print the tree\n");
    printf("\t6 -> Upload from file\n");
    printf("\t7 -> Quit\n");
}
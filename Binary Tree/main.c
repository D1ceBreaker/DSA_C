#include <stdio.h>
#include "user.h"
void commands();
void menu();
int main() {
    menu();
    return 0;
}
void menu(){
    commands();
    Tree* data = calloc(1, sizeof(Tree));
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
                SpecialSearch(data);
                break;
            case 5:
                if (data->root){
                    ascetic(data, data->root);
                }
                else printf("Tree is empty\n");
                break;
            case 6:
                Upload(data);
            default:
                printf("Unidentified key\n");
                break;
        }
        option = getPosInt();
    }
    tree_delete(data->root);
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
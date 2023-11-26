#include <stdio.h>
#include "user.h"
void commands();
void menu();
int main() {
    menu();
    return 0;
}
void menu(){
    Table* data = Initialise("strs.bin");
    if (data == NULL) return;
    commands();

    unsigned int option = getPosInt();
    while (option != 6){
        switch (option) {
            case 1:
                AddElement(data);
                break;
            case 2:
                Find(data);
                break;
            case 3:
                Delete(data);
                break;
            case 4:
                print(data);
                break;
            case 5:
                Upload(data);
                break;
            default:
                printf("Unidentified key\n");
                break;
        }
        commands();
        option = getPosInt();

    }
    fclose(data->file);
    fclose(data->str_file);
    free(data);
}

void commands(){
    printf("List of options:\n");
    printf("\t1 -> Add an element\n");
    printf("\t2 -> Find key\n");
    printf("\t3 -> Delete key\n");
    printf("\t4 -> Print the table\n");
    printf("\t5 -> Upload from file\n");
    printf("\t6 -> Quit\n");
}
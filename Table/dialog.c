#include "dialog.h"
#include "table.h"
#include "user.h"
#include <stdio.h>

void menu(){
    Table* data = NULL;
    int option = getPosInt();
    while (option != 8){
        switch (option) {
            case 1:
                data = CreateTable();
                break;
            case 2:
                data = AddElement(data);
                break;
            case 3:
                FindElement(data);
                break;
            case 4:
                data = DeleteElement(data);
                break;
            case 5:
                DeleteTable(data);
                break;
            case 6:
                print(data);
                break;
            case 7:
                commands();
                break;

            default:
                printf("Unidentified key\n");
                break;
        }
        option = getPosInt();
    }

}
void commands(){
    printf("List of options:\n");
    printf("\t1 -> Create the table\n");
    printf("\t2 -> Add an element\n");
    printf("\t3 -> Find key/version\n");
    printf("\t4 -> Delete an element\n");
    printf("\t5 -> Delete the table\n");
    printf("\t6 -> Print the table\n");
    printf("\t7 -> Help\n");
    printf("\t8 -> Quit\n");
}
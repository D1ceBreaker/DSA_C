#include "dialog.h"
#include "table.h"
#include "user.h"
#include <stdio.h>

void menu(){
    Table* data = NULL;
    int flag = 1;
    commands();
    int option = getPosInt();
    while (option != 7){
        switch (option) {
            case 1:
                if (flag){
                    data = CreateTable();
                    flag = 0;
                }
                else{
                    printf("A table already exists\n");
                }
                break;
            case 2:
                if (flag == 0){
                    data = AddElement(data);
                }
                else{
                    printf("No table available\n");
                }
                break;
            case 3:
                if (flag == 0){
                    FindElements(data);
                }
                else{
                    printf("No table available\n");
                }
                break;
            case 4:
                if (flag == 0){
                    data = CompressTable(data);
                }
                else{
                    printf("No table available\n");
                }
                break;
            case 5:
                if (flag == 0){
                    Print(data);
                }
                else{
                    printf("No table available\n");
                }
                break;
            case 6:
                commands();
                break;

            default:
                printf("Unidentified key\n");
                break;
        }
        option = getPosInt();

    }
    Delete(data);
}

void commands(){
    printf("List of options:\n");
    printf("\t1 -> Create a table\n");
    printf("\t2 -> Add an element\n");
    printf("\t3 -> Find key/version\n");
    printf("\t4 -> Compress the table\n");
    printf("\t5 -> Print the table\n");
    printf("\t6 -> Help\n");
    printf("\t7 -> Quit\n");
}
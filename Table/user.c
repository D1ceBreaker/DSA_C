#include "user.h"
#include <stdio.h>
#include <stdlib.h>

Table* CreateTable(){
    printf("Enter the size of the table\n");
    int msize = getPosInt();
    Table* data = create(msize);
    return data;
}
Table* AddElement(Table* data){
    printf("Enter the key\n");
    int key = getPosInt();
    printf("Enter the information\n");
    char* info = readline();
    Table* check = push(data, key, info);
    if (check == NULL){
        return data;
    }
    else {
        return check;
    }
}
Table* DeleteElement(Table* data){
    printf("Enter the key\n");
    int key = getPosInt();
    printf("Enter the release version, -1 if you need all versions\n");
    int release = -1;
    int n = scanf("%d", &release);
    while (n <= 0){
        scanf("%*c");
        n = scanf("%d", &release);
    }

    data = delete(data, key, release);
    return data;
}

void DeleteTable(Table* data){
    table_delete(data);
}
int FindElement(Table* data){
    printf("Enter the key\n");
    int key = getPosInt();
    printf("Enter the release version, -1 if you need all versions\n");
    int release = -1;
    int n = scanf("%d", &release);
    while (n <= 0){
        scanf("%*c");
        n = scanf("%d", &release);
    }
    Table* result = makeTableFromSearch(data, key, release);
    if (result == NULL){
        printf("No such keys or release versions were found\n");
        return 0;
    }
    print(result);
    free(result->space);
    free(result);
    return 1;
}
char* readline(){
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

int getPosInt(){
    int n;
    int r = scanf("%d", &n);
    while (r <= 0){
        scanf("%*c");
        r = scanf("%d", &n);
    }
    while (n < 0){
        n = getPosInt();
    }
    return n;
}
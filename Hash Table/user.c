#include "user.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
Table* CreateTable(){
    printf("Enter the size of the table\n");
    unsigned size = getPosInt();
    Table* data = create((int)size);
    return data;
}

Table* AddElement(Table* data){
    printf("Enter the key\n");
    unsigned key = getPosInt();
    printf("Enter the information\n");
    char* info = readline();
    data = push(data, key, info);
    return data;
}

void FindElements(Table* data){
    printf("Enter the key\n");
    unsigned key = getPosInt();
    printf("Enter the version, 0 - all\n");
    unsigned rel = getPosInt();

    Table* f = create_from_search(data, key, rel);
    print(f);
    free(f->space[0]);
    free(f->space);
    free(f);
}

Table* CompressTable(Table* data){
    data = compress(data);
    return data;
}
void Print(Table* data){
    print(data);
}
void Delete(Table* data){
    delete(data);
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

static char* readline(){
    scanf("%*c");
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
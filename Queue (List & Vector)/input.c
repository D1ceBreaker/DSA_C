#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"
#include "input.h"

Triple* get_passengers(int* n){
    char* a = input_line();
    if (a == NULL) return NULL;
    int len = 0;
    char** line = input_triple(a, &len);
    Triple* data = get_triple(line, len);
    while (data == NULL){
        printf("Arrival time and service time must be positive numbers\n");
        a = input_line();
        line = input_triple(a, &len);
        data = get_triple(line, len);
    }
    *n = len;
    return data;
}
char* input_line(){
    char* line = calloc(1, sizeof(char));
    int len = 0;
    int n = getchar();
    while (n != '\n'){
        if (n == EOF) return NULL;
        len++;
        line = (char*) realloc(line, len * sizeof(char));
        line[len - 1] = (char)n;
        line[len] = '\0';
        n = getchar();
    }
    return line;
}
// a/1/2 d/2/1 c/13/1 ... \n
char** input_triple(char* line, int* n){
    char** list = NULL;
    int len = 0;
    char* data = strdup(line);
    char* triad = strtok(data, " ");
    while (triad != NULL){

        if (strlen(triad) > 0){
            len++;
            list = (char**) realloc(list, sizeof(char*) * len);
            list[len - 1] = triad;
        }
        triad = strtok(NULL, " ");

    }
    *n = len;
    return list;
}
// a/2/1
Triple* get_triple(char** list, int n){
    Triple* array = calloc(n, sizeof(Triple));
    for (int i = 0; i < n; i++){
        char* data = list[i];
        char* name = strtok(data, "/");
        char* arrival = strtok(NULL, "/");
        char* time = strtok(NULL, "/");
        int ia = 0, it = 0;
        if (isNumber(arrival)){
            ia = chartoint(arrival);
        }
        else return NULL;
        if (isNumber(time)){
            it = chartoint(time);
        }
        else return NULL;
        Triple ex = {name, ia, it};
        array[i] = ex;
    }

    return array;
}

int isNumber(char* data){
    for (int i = 0; i < strlen(data); i++){
        if ('0' <= data[i] && data[i] <= '9'){
            continue;
        } else{
            return 0;
        }
    }
    return 1;
}
int chartoint(char* data){
    int n = 0;
    for (int i = 0; i < strlen(data); i++){
        if (n > INT_MAX / 10){
            return 1;
        }
        n *= 10;
        n += (data[i] - '0');
    }
    return n;
}

void getPosInt(char* format, int* num){
    int n = getInt(format, num);
    while (n == 0){
        n = getInt(format, num);
    }
}
int getInt(char* format, int* num){
    int n = scanf(format, num);
    while (n <= 0){
        scanf("%*c");
        n = scanf(format, num);
    }
    if (*num > 0){
        return 1;
    }
    return 0;
}
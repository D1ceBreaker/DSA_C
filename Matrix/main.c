#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
void matrix_input(Matrix* data, int m);
void task(Matrix* data, int m);

int main() {
    int m;
    printf("Enter the number of lines:\n");
    input(&m, 0);
    Line* list = calloc(m, sizeof(Line));
    Matrix data = {m, list};
    matrix_input(&data, m);
    print(&data, m);
    printf("-------------------\n");
    task(&data, m);
    print(&data, m);
    clear(&data, m);
    free(list);
    return 0;
}

void matrix_input(Matrix* data, int m){
    for (int i = 0; i < m; i++){
        printf("Enter the length of the line:\n");
        int n;
        input(&n, 0);
        printf("Enter the content of the line\n");

        int* array = (int*)calloc(n, sizeof(int));
        for (int j = 0; j < n; j++){
            input(array + j, 1);
        }
        Line new = {n, array};
        data->list[i] = new;
    }
}

void task(Matrix* data, int m){
    for (int i = 0; i < m; i++){
        int len = data->list[i].n;
        for (int j = 0; j < len / 2; j++){
            data->list[i].data[j] += data->list[i].data[len - j - 1];
            data->list[i].data[len - j - 1] = data->list[i].data[j] - data->list[i].data[len - j - 1];
            data->list[i].data[j] -= data->list[i].data[len - j - 1];
        }
    }
}
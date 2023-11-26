#include <stdlib.h>
#include <stdio.h>
#include "lib.h"

void input(int *a, int mode){
    // 0 -> singular entry
    // 1 -> string of numbers input
    int n;
    do{
        n = scanf("%d", a);
        if (n < 0){
            printf("An error occurred");
            exit(0);
        }
        if (n == 0){
            mode ? printf("Carry on entering the string strictly with numbers\n") :
            printf("Enter a number\n");
            scanf("%*[^\n]");
        }
    } while (n == 0);

}

void print(Matrix* square, int m){
    printf("The matrix is -->\n");
    for (int i = 0; i < m; i++){
        printf("%d.| ", i + 1);
        for (int j = 0; j < square->list[i].n; j++){
            printf("%d ", square->list[i].data[j]);
        }
        printf("\n");
    }
}
void clear(Matrix* square, int m){
    for (int i = 0; i < m; i++){
        free(square->list[i].data);
    }
}



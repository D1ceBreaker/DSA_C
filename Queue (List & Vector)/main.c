#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "queue.h"
int comparator(Triple* ex1, Triple* ex2);
void print_out(Queue* data, int terminals, int cnt);
void round_robin(Triple* list, int len, int terminals, int ql);
int main() {

    int n;
    //printf("Enter the passengers\n");
    Triple* list = get_passengers(&n);
    int ql = 0;
    printf("Enter the size of queue\n");
    scanf("%d", &ql);
    int terminals = 0;
    printf("Enter the number of terminals\n");
    scanf("%d", &terminals);
    qsort(list, n, sizeof(Triple),  (int (*)(const void*, const void*)) comparator);
    round_robin(list, n, terminals, ql);
    return 0;
}
void round_robin(Triple* list, int len, int terminals, int ql){
    Queue* data = calloc(terminals, sizeof(Queue));
    for (int i = 0; i < terminals; i++){
        data[i] = *create(ql);
    }

    int flag = 1;
    int cnt = 0;
    int pos = 0;
    int q = 0;
    print_out(data, terminals, cnt);
    while (flag){
        int print = 0;
        if (cnt == list[pos].arrival){
            push(&data[q], list[pos]);
            pos++;
            q++;
            print = 1;
            if (q >= terminals) q = 0;
        }

        for (int i = 0; i < terminals; i++){
            Triple first;
            int n = peek(&data[i], &first);
            if (n){
                if (first.time >= cnt + first.arrival){
                    pop(&data[i]);
                    print = 1;
                }
            }
        }

        int end = 0;
        for (int i = 0; i < terminals; i++){
            if (data[i].len > 0){
                end = 1;
                break;
            }
        }
        if (print) print_out(data, terminals, cnt);
        cnt++;
        if (end == 0 && pos >= len) flag = 0;

    }
}

int comparator(Triple* ex1, Triple* ex2){
    return ex1->arrival - ex2->arrival;
}
void print_out(Queue* data, int terminals, int cnt){
    printf("Time: %d\n", cnt);
    for (int k = 0; k < terminals; k++){
        printf("%d: ", k + 1);
        for (int i = 0; i < data[k].len; i++){
            printf("%s ", data[k].list[i].name);
        }
        printf("\n");
    }
    printf("------------------\n");
}
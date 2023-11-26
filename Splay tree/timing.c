#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "user.h"
#define START_NUM 100000
#define PLUS 1000
void assemble(FILE* file, int num);
char* random_string(int len);
Splay* load(FILE* file, int num);
char** random_array(int num);
void Timing();
int main(){
    srand(time(NULL));
    Timing();
    return 0;
}

void Timing(){
    FILE* test = fopen("tree.txt", "w+");
    FILE* results = fopen("result.txt", "w+");
    assemble(test, 10 * START_NUM);
    fclose(test);

    for (int epochs = 1; epochs <= 10; epochs++){
        printf("%d\n", epochs);

        double avg = 0;
        int s = 1;//30
        for (int k = 0; k < s; k++){
            FILE* tree = fopen("tree.txt", "r+");
            FILE* pr = fopen("p.txt", "w+");
            Splay* data = load(tree, START_NUM * epochs);
            char** strs = random_array(PLUS);

            clock_t start = clock();
            inOrder(data->root, pr);
            clock_t end = clock();

            avg += (double) (end - start) / CLOCKS_PER_SEC;
            free_tree(data->root);
            fclose(tree);
            fclose(pr);
        }
        avg /= s;
        fprintf(results, "%lf\n", avg);
    }
    fclose(results);
}

void assemble(FILE* file, int num){
    int len = 15;
    for (int i = 0; i < num; i++){
        char* s = random_string(len);
        fputs(s, file);
    }
}

char* random_string(int len){
    char* data = calloc(len + 1, sizeof(char));
    for (int i = 0; i < len; i++){
        data[i] = (char) (rand() % ('a' - 'z') + 'a');
    }
    return data;
}

Splay* load(FILE* file, int num){
    Splay* data = calloc(1, sizeof(Splay));
    for (int i = 0; i < num; i++){
        char* key = calloc(16, sizeof(char));
        fgets(key, 16, file);
        push(data, key, 0);
    }
    return data;
}

char** random_array(int num){
    char** strs = calloc(num, sizeof(char*));
    for (int l = 0; l < num; l++){
        strs[l] = random_string(15);
    }
    return strs;
}

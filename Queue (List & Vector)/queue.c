#include <stdlib.h>
#include "queue.h"
Queue* create(int mem){
    Queue* example = malloc(sizeof(Queue));
    example->list = malloc(sizeof(Triple) * mem);
    example->mem = mem;
    example->len = 0;
    return example;
}
int push(Queue* data, Triple example){
    if (data->mem == data->len){
        return 0;
    }
    data->list[data->len] = example;
    data->len += 1;
    return 1;
}
int pop(Queue* data){
    if (data->len == 0){
        return 0;
    }
    for (int i = 0; i < data->len - 1; i++){
        data->list[i] = data->list[i + 1];
    }
    data->len -= 1;
    return 1;
}
int peek(Queue* data, Triple* result){
    if (data->len == 0){
        return 0;
    }
    *result = data->list[0];
    return 1;
}

void delete(Queue* data){
    free(data->list);
    free(data);
}
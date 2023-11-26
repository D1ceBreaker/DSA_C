#ifndef QUEUE_H
#define QUEUE_H
typedef struct Triple{
    char* name;
    int arrival;
    int time;
}Triple;
//vector implementation
typedef struct Queue{
    Triple* list;
    int mem;
    int len;
}Queue;

Queue* create(int mem);
int push(Queue* data, Triple example);
int pop(Queue* data);
int peek(Queue* data, Triple* result);
void delete(Queue* data);

#endif //QUEUE_H

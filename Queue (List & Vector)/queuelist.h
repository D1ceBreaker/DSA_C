
#ifndef QUEUELIST_H
#define QUEUELIST_H
typedef struct Triple{
    char* name;
    int arrival;
    int time;
    struct Triple* next;
}Triple;
//vector implementation
typedef struct Queue{
    Triple* head;
    Triple* tail;
    int len;
}Queue;

Queue* create(int mem);
int push(Queue* data, Triple example);
int pop(Queue* data);
int peek(Queue* data, Triple* result);
void delete(Queue* data);
#endif //QUEUELIST_H

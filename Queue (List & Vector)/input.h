#ifndef INPUT_H
#define INPUT_H
#include "queue.h"
Triple* get_passengers(int* n);
char* input_line();
char** input_triple(char* line, int* n);
Triple* get_triple(char** list, int n);

int getInt(char* format, int* num);
void getPosInt(char* format, int* num);

int isNumber(char* data);
int chartoint(char* data);

#endif //INPUT_H

#ifndef MATRIX_H
#define MATRIX_H
typedef struct Line{
    int n;
    int* data;
}Line;
typedef struct Matrix {
    int m;
    Line* list;
}Matrix;
#endif //MATRIX_H

#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct KeySpace{
    unsigned int key;
    unsigned int rel;
    int offset; //offset of string
    int size; //string size

}KeySpace;

typedef struct Table{
    FILE* file;
    FILE* str_file;
    int password;
    int start;

}Table;
Table* open(FILE* main, FILE* string);
int add(Table* data, unsigned int key, char* string);

Table* search(Table* data, FILE* file, unsigned int key, unsigned int rel);


int delete(Table* data, unsigned int key, unsigned int rel);
void rewrite(Table* data, int i);

static void download(FILE* file, unsigned int* key, unsigned int* rel);
static void download_else(FILE* file, int* offset, int* size);

void print(Table* data);
static int len_number(unsigned int n);
static void print_info(unsigned int key, unsigned int rel, char* string, int l);
static void line(int l, char s);
static void cap(int l);
#endif //TABLE_H

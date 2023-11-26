#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Info{
    unsigned int value;
    unsigned int release;
    struct Info* next;
}Info;

typedef struct Node{
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    char* key;
    Info* list;
}Node;

typedef struct Tree{
    Node* root;
}Tree;

void add(Tree* data, char* key, unsigned int value);
int push(Node* cur, Node* new);


int del(Tree* data, Node* delete);
void free_node(Node* node);
int delete_list(Node* host, unsigned int rel);
int delete(Tree* data, char* key, unsigned int rel);


void ascetic(Tree* data, Node* cur);
static int isZigZag(Node* cur);
static int position(Node* cur);
static int find(Node* cur, char* key, int* height);


Node* findMin(Node* cur);
Node* search(Node* cur, char* key);
void inOrder(Node* cur, FILE* file);
void tree_delete(Node* cur);
#endif //TREE_H

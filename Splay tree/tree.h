#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <stdio.h>
typedef struct Node{
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    char* key;
    unsigned int value;
}Node;

typedef struct Splay{
    Node* root;
}Splay;


int search(Splay* data, char* key);
static Node* rightRotate(Splay* data, Node* x);
static Node* leftRotate(Splay* data, Node* x);
static Node* splay(Splay* data, Node* cur, char* key);

Node* make(char* key, unsigned int value);
static int insert(Node* cur, Node* new);
int push(Splay* data, char* key, unsigned int value);

Splay* delete(Splay* data, char* key);
void free_tree(Node* cur);

void inOrder(Node* cur, FILE* file);

char* findMax(Node* cur);
void search_max(Node* cur, char* string, char** max);
int searchMax(Splay* data, char* string);

static int position(Node* cur);
static int isZigZag(Node* cur);
static int find(Node* cur, char* key, int* height);
void ascetic(Splay* data, Node* cur);
#endif //TREE_H

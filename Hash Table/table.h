#ifdef TABLE_H
#endif

#ifndef TABLE_H
#define TABLE_H

typedef struct Item{
    char* string;
}Item;

typedef struct Node{
    unsigned int release;
    Item* info;
    struct Node* next;
}Node;

typedef struct KeySpace{
    unsigned int key;
    Node* node;
    struct KeySpace* next;
}KeySpace;

typedef struct Table{
    int size;
    KeySpace** space;
}Table;




//create
Table* create(int size);

//add
Table* push(Table* data, unsigned int key, char* string);
 unsigned hash(unsigned int key);

//find
Table* create_from_search(Table* data, unsigned int key, unsigned int release);
Node* search(Table* data, unsigned int key, unsigned int release);

//compress
Table* compress(Table* data);

//delete
void delete(Table* data);

//print
void print(Table* data);
static void cap(int l);
static void line(int l, char s);
static void print_info(Table* data, unsigned int key, unsigned int release, char* string, int l);
static int len_number(unsigned int n);
#endif //TABLE_H
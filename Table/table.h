#ifdef TABLE_H

#endif

#ifndef TABLE_H
#define TABLE_H
typedef struct {
    char* data;
}Item;

typedef struct {
    int key;
    unsigned int rel;
    Item* info;
}KeySpace;

typedef struct {
    KeySpace* space;
    int* keys;
    int len;
    int msize;
}Table;

//create
Table* create(int msize);

//add
Table* push(Table* data, int key, char* string);
static int comparator(const int* key1, const int* key2);
static int isKey(Table* data, int key);
static int countKey(Table* data, int key);

//find
KeySpace* search(Table* data, int key, int release, int* space_len);
Table* makeTableFromSearch(Table* data, int key, int release);

//delete
void table_delete(Table* data);

//print out
void print(Table* data);
static void cap(int l);
static void line(int l, char s);
static int len_number(int n);
static void print_info(int key, int release, char* string, int l);

//delete el
void delete_key(KeySpace* element);
Table* delete(Table* data, int key, int release);

#endif //TABLE_H
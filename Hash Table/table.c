#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 unsigned int hash(unsigned int key){
    unsigned long long int h = INT_MAX;
    while (key > 0){
        unsigned s = key % 10;
        key /= 10;
        h = h * 37 + s;
    }
    return h;
}

Table* create(int size){
    Table* data = calloc(1, sizeof(Table));
    data->size = size;
    data->space = calloc(size, sizeof(KeySpace*));

    return data;
}

Table* push(Table* data, unsigned int key, char* string){
    //create information
    Item* element = calloc(1, sizeof(Item));
    element->string = string;

    //find placement
    int pos = hash(key);
    int flag = 1;
    KeySpace* iterator = data->space[pos];
    KeySpace* predecessor = NULL;
    KeySpace* f = NULL;
    while(iterator){
        if (iterator->key == key){
            f = iterator;
            flag = 0;
            break;
        }
        predecessor = iterator;
        iterator = iterator->next;
    }
    if (flag){
        KeySpace* example = calloc(1, sizeof(KeySpace));
        example->key = key;
        example->node = NULL;
        example->next = NULL;
        if (predecessor){
            predecessor->next = example;
        }
        else{
            data->space[pos] = example;
        }
        f = example;
    }
    //push into branch

    Node* new = calloc(1, sizeof(Node));
    new->info = element;
    new->next = NULL;

    unsigned int rel_max = 0;

    Node* ptr = f->node;
    Node* pred = NULL;
    while (ptr){
        if (ptr->release > rel_max) rel_max = ptr->release;
        pred = ptr;
        ptr = ptr->next;
    }
    new->release = rel_max + 1;
    if (pred){
        pred->next = new;
    }
    else{
        f->node = new;
    }
    return data;
}

Node* search(Table* data, unsigned int key, unsigned int release){
    int pos = hash(key);
    KeySpace* ptr = data->space[pos];
    while (ptr){
        if (ptr->key == key) break;
        ptr = ptr->next;
    }
    if (ptr == NULL) return NULL;

    Node* i = ptr->node;
    if (release == 0) return i;
    while (i){
        if (i->release == release) break;
        i = i->next;
    }
    return i;
}
Table* create_from_search(Table* data, unsigned int key, unsigned int release){
    Table* result = create(1);
    KeySpace* element = calloc(1, sizeof(KeySpace));
    element->next = NULL;
    element->node = search(data, key, release);
    element->key = key;
    result->space[0] = element;
    return result;
}

Table* compress(Table* data){
    for (int i = 0; i < data->size; i++){
        KeySpace* ptr = data->space[i];
        while (ptr){
            Node* el = ptr->node;
            unsigned int max = 0;
            Node* save = NULL;
            while (el){
                if (el->release > max){
                    save = el;
                    max = el->release;
                }
                el = el->next;
            }
            Node* iterator = ptr->node;
            Node* prev = NULL;
            while (iterator){
                prev = iterator;
                iterator = iterator->next;
                if (prev != save){
                    free(prev->info->string);
                    free(prev->info);
                    free(prev);
                }
            }
            ptr->node = save;
            ptr = ptr->next;
        }
    }
    return data;
}

void delete(Table* data){
    for (int i = 0; i < data->size; i++){
        KeySpace* ptr = data->space[i];
        KeySpace* prev_ptr = NULL;
        while (ptr){
            Node* el = ptr->node;
            Node* prev_el = NULL;
            while(el){
                prev_el = el;
                el = el->next;
                free(prev_el->info->string);
                free(prev_el->info);
                free(prev_el);
            }

            prev_ptr = ptr;
            ptr = ptr->next;
            free(prev_ptr);
        }
    }
    free(data->space);
    free(data);
}

void print(Table* data){
    int max = 0;

    for (int i = 0; i < data->size; i++){
        KeySpace* ptr = data->space[i];
        while (ptr){
            Node* el = ptr->node;
            while (el){
                int a = (int)strlen(el->info->string);
                if (a > max){
                    max = a;
                }
                el = el->next;
            }
            ptr = ptr->next;
        }
    }

    int l = max + 7;
    for (int i = 0; i < 7 + 10 + 10 + l + 1 + 1; i++){
        printf("_");
    }
    printf("\n");
    cap(l);
    printf("\n");
    for (int i = 0; i < data->size; i++){
        KeySpace* ptr = data->space[i];
        while (ptr){
            Node* el = ptr->node;
            while (el){
                line(l, ' ');
                printf("\n");
                print_info(data, ptr->key, el->release, el->info->string, l);
                printf("\n");
                line(l, '_');
                printf("\n");
                el = el->next;
            }
            ptr = ptr->next;
        }
    }
}

static int len_number(unsigned int n){
    int cnt = 0;
    if (n == 0) return 1;
    while (n > 0){
        n /= 10;
        cnt++;
    }
    return cnt;
}
static void print_info(Table* data, unsigned int key, unsigned int release, char* string, int l){
    printf("| ");
    int h = hash(key);
    printf("%d", h);
    for (int i = 0; i < 5 - len_number(h); i++){
        printf(" ");
    }

    printf("| ");
    printf("%u", key);
    for (int i = 0; i < 8 - len_number(key); i++){
        printf(" ");
    }
    printf("| ");
    printf("%u", release);
    for (int i = 0; i < 8 - len_number(release); i++){
        printf(" ");
    }
    printf("| ");
    printf("%s", string);
    for (int i = 0; i < l - strlen(string) - 1; i++){
        printf(" ");
    }
    printf("|");
}

static void line(int l, char s){
    printf("|");
    for (int i = 0; i < 6; i++){
        printf("%c", s);
    }
    printf("|");
    for (int i = 0; i < 9; i++){
        printf("%c", s);
    }
    printf("|");
    for (int i = 0; i < 9; i++){
        printf("%c", s);
    }
    printf("|");
    for (int i = 0; i < l; i++){
        printf("%c", s);
    }
    printf("|");
}
static void cap(int l){
    printf("|_hash_|___key___|_release_|");
    for (int i = 0; i < l/2 - 2; i++){
        printf("_");
    }
    printf("info");
    for (int i = 0; i < l/2 - 2; i++){
        printf("_");
    }
    if (l % 2 == 1) printf("_");
    printf("|");
}

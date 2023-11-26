#include "table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
static int comparator(const int* key1, const int* key2){
    return *key1 - *key2;
}

Table* create(int msize){
    Table* data = calloc(1, sizeof(Table));
    data->space = calloc(msize, sizeof(KeySpace));
    data->keys = calloc(0, sizeof(int));
    data->msize = msize;
    data->len = 0;

    return data;
}
Table* push(Table* data, int key, char* string){
    if (data->len == data->msize) return NULL;
    //make new element
    KeySpace new;
    //make new info unit
    Item* n = calloc(1, sizeof(Item));
    n->data = string;

    new.info = n;
    new.key = key;

    //update release version; 0 if none
    int release = isKey(data, key);
    new.rel = release;

    //put new key and element into according structures
    data->keys = realloc(data->keys, (data->len + 1) * sizeof(int));
    data->keys[data->len] = key;
    data->space[data->len] = new;
    data->len += 1;

    //sort keys for further binary searches
    qsort(data->keys, data->len, sizeof(int),
          (int(*) (const void*, const void*)) comparator);

    return data;
}
static int isKey(Table* data, int key){
    //binary search of the key
    int right = 0;
    int left = data->len;

    while (right < left){
        int mid = (right + left) / 2;
        if (data->keys[mid] < key){
            right = mid + 1;
        }
        else if (data->keys[mid] > key){
            left = mid - 1;
        }
        else{
            return countKey(data, key);
        }
    }
    return 0;

}
static int countKey(Table* data, int key){
    int cnt = 0;
    for (int i = 0; i < data->len; i++){
        if (data->keys[i] == key){
            cnt++;
        }
    }
    return cnt;
}



KeySpace* search(Table* data, int key, int release, int* space_len){
    KeySpace* range = NULL;
    int len = 0;

    for (int i = 0; i < data->len; i++){
        if (data->space[i].key == key){
            if (release == -1){
                range = (KeySpace*) realloc(range, (len + 1) * sizeof(KeySpace));
                range[len] = data->space[i];
                len++;
            }
            else if (release == data->space[i].rel){
                range = (KeySpace*) realloc(range, (len + 1) * sizeof(KeySpace));
                range[len] = data->space[i];
                len++;
                break;
            }

        }
    }
    *space_len = len;
    return range;
}

Table* makeTableFromSearch(Table* data, int key, int release){
    int len = 0;
    KeySpace* range = search(data, key, release, &len);
    if (range == NULL) return NULL;
    Table* result = calloc(1, sizeof(Table));
    result->len = len;
    result->msize = len;
    result->space = range;
    return result;
}



Table* delete(Table* data, int key, int release){
    for (int i = 0; i < data->len; i++){
        if (data->space[i].key == key){
            if (release == -1){
                delete_key(&(data->space[i]));
                for (int j = i + 1; j < data->len; j++){
                    data->space[j - 1] = data->space[j];
                }
                i--;
                data->len -= 1;
            }
            else if (data->space[i].rel == release){
                delete_key(&(data->space[i]));
                for (int j = i + 1; j < data->len; j++){
                    data->space[j - 1] = data->space[j];
                }
                i--;
                data->len -= 1;
                break;
            }
        }
    }
    return data;
}



void delete_key(KeySpace* element){
    //free(element->info->data);
    free(element->info);
}

void table_delete(Table* data){
    for (int i = 0; i < data->len; i++){
       // free(data->space[i].info->data);
        free(data->space[i].info);
    }
    free(data->space);
    free(data->keys);
}



void print(Table* data){
    int max = 0;
    for (int i = 0; i < data->len; i++){
        int a = strlen(data->space[i].info->data);
        if (a > max){
            max = a;
        }
    }

    int l = max + 7;
    for (int i = 0; i < 10 + 10 + l + 1 + 1; i++){
        printf("_");
    }
    printf("\n");
    cap(l);
    printf("\n");
    for (int i = 0; i < data->len; i++){
        line(l, ' ');
        printf("\n");
        print_info(data->space[i].key, data->space[i].rel, data->space[i].info->data, l);
        printf("\n");
        line(l, '_');
        printf("\n");
    }

}
static int len_number(int n){
    int cnt = 0;
    if (n == 0) return 1;
    while (n > 0){
        n /= 10;
        cnt++;
    }
    return cnt;
}
static void print_info(int key, int release, char* string, int l){
    printf("| ");
    printf("%d", key);
    for (int i = 0; i < 8 - len_number(key); i++){
        printf(" ");
    }
    printf("| ");
    printf("%d", release);
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
    printf("|___key___|_release_|");
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
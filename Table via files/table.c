#include "table.h"
#include <string.h>

Table* open(FILE* main, FILE* string){
    Table* data = calloc(1, sizeof(Table));
    data->file = main;
    data->str_file = string;
    data->password = 8;
    data->start =  data->password + 2 * (int) sizeof(int);
    return data;
}

int add(Table* data, unsigned int key, char* string){
    int len = 0;
    int msize = 0;

    fseek(data->file, data->password, SEEK_SET);
    fread(&len, sizeof(int), 1, data->file);
    fread(&msize, sizeof(int), 1, data->file);

    if (len == msize) return 1;

    unsigned int fkey, frel;
    unsigned int max = 0;
    int offset = 0;
    int last_len = 0;

    for (int i = 0; i < len; i++){
        fseek(data->file, (long) sizeof(KeySpace) * i + data->start, SEEK_SET);
        download(data->file, &fkey, &frel);
        if (key == fkey && frel > max) max = frel;
        if (i == len - 1){
            fread(&offset, sizeof(int), 1, data->file);
            fread(&last_len, sizeof(int), 1, data->file);
        }
    }
    max++;
    int size = (int)strlen(string);
    int new = offset + last_len;
    if (len == 0) new = 0;
    fseek(data->str_file, new, SEEK_SET);
    fwrite(string, sizeof(char), size, data->str_file);

    fseek(data->file, (long) sizeof(KeySpace) * len + data->start, SEEK_SET);
    fwrite(&key, sizeof(unsigned int), 1, data->file);
    fwrite(&max, sizeof(unsigned int), 1, data->file);
    fwrite(&new, sizeof(int), 1, data->file);
    fwrite(&size, sizeof(int), 1, data->file);

    len++;
    fseek(data->file, data->password, SEEK_SET);
    fwrite(&len, sizeof(int), 1, data->file);

    free(string);
    return 0;
}

Table* search(Table* data, FILE* file, unsigned int key, unsigned int rel){
    Table* found = calloc(1, sizeof(Table));
    found->file = file;
    found->str_file = data->str_file;
    found->password = data->password;
    found->start = data->start;
    int new_len = 0;

    int len = 0;
    fseek(data->file, data->password, SEEK_SET);
    fread(&len, sizeof(int), 1, data->file);

    if (len == 0) return NULL;

    unsigned int fkey, frel;
    int offset, size;

    for (int i = 0; i < len; i++) {
        fseek(data->file, (long) sizeof(KeySpace) * i + data->start, SEEK_SET);
        download(data->file, &fkey, &frel);
        if (key == fkey){
            download_else(data->file, &offset, &size);
            fseek(found->file, (long) sizeof(KeySpace) * new_len + found->start, SEEK_SET);
            if (rel == 0){
                fwrite(&key, sizeof(unsigned int), 1, found->file);
                fwrite(&frel, sizeof(unsigned int), 1, found->file);
                fwrite(&offset, sizeof(int), 1, found->file);
                fwrite(&size, sizeof(int), 1, found->file);

                new_len++;

            }
            else if (rel == frel){

                fwrite(&key, sizeof(unsigned int), 1, found->file);
                fwrite(&frel, sizeof(unsigned int), 1, found->file);
                fwrite(&offset, sizeof(int), 1, found->file);
                fwrite(&size, sizeof(int), 1, found->file);

                new_len++;
                break;
            }
        }
    }
    fseek(found->file, found->password, SEEK_SET);
    fwrite(&new_len, sizeof(int), 1, found->file);
    fwrite(&new_len, sizeof(int), 1, found->file);
    return found;
}


int delete(Table* data, unsigned int key, unsigned int rel){
    int len = 0;
    fseek(data->file, data->password, SEEK_SET);
    fread(&len, sizeof(int), 1, data->file);

    unsigned int fkey, frel;
    for (int i = 0; i < len; i++){
        fseek(data->file, (long) sizeof(KeySpace) * i + data->start, SEEK_SET);
        download(data->file, &fkey, &frel);
        if (key == fkey){
            if (rel == 0){
                rewrite(data, i);
                i--;
            }

            else if (rel == frel){
                rewrite(data, i);
                break;
            }
        }
    }
    return 0;
}

void rewrite(Table* data, int i){
    int len = 0;
    fseek(data->file, data->password, SEEK_SET);
    fread(&len, sizeof(int), 1, data->file);

    if (len == 1 || i == len - 1){
        len--;
        fseek(data->file, data->password, SEEK_SET);
        fwrite(&len, sizeof(int), 1, data->file);
        return;
    }
    int pr_offset, pr_size;
    download_else(data->file, &pr_offset, &pr_size);

    fseek(data->file, (long) sizeof(KeySpace) * (len - 1) + data->start, SEEK_SET);
    unsigned int r_key, r_rel;
    int r_offset, r_size;

    download(data->file, &r_key, &r_rel);
    download_else(data->file, &r_offset, &r_size);

    len--;
    fseek(data->file, data->password, SEEK_SET);
    fwrite(&len, sizeof(int), 1, data->file);

    fseek(data->file, (long) sizeof(KeySpace) * i + data->start, SEEK_SET);
    fwrite(&r_key, sizeof(unsigned int), 1, data->file);
    fwrite(&r_rel, sizeof(unsigned int), 1, data->file);
    fwrite(&pr_offset, sizeof(int), 1, data->file);
    fwrite(&r_size, sizeof(int), 1, data->file);

    char* last = calloc(r_size, sizeof(char ));
    fseek(data->str_file, r_offset, SEEK_SET);
    fread(last, sizeof(char ), r_size, data->str_file);

    int length = r_offset - (pr_offset + pr_size);
    if (length == 0){
        fseek(data->str_file, pr_offset, SEEK_SET);
        fwrite(last, sizeof(char), r_size, data->str_file);
    }
    else{
        char* between = calloc(length, sizeof(char));
        fseek(data->str_file, pr_offset + pr_size, SEEK_SET);
        fread(between, sizeof(char), length, data->str_file);

        fseek(data->str_file, pr_offset, SEEK_SET);
        fwrite(last, sizeof(char), r_size, data->str_file);
        fwrite(between, sizeof(char), length, data->str_file);

        free(between);
    }
    free(last);

    int offset;
    for (int j = i + 1; j < len; j++){
        fseek(data->file, (long)(sizeof(KeySpace) * j + 2 * sizeof(int) + data->start), SEEK_SET);
        fread(&offset, sizeof(int), 1, data->file);
        offset -= (pr_size);
        offset += r_size;
        fseek(data->file, (long)(sizeof(KeySpace) * j + 2 * sizeof(int) + data->start), SEEK_SET);
        fwrite(&offset, sizeof(int), 1, data->file);
    }
}

static void download(FILE* file, unsigned int* key, unsigned int* rel){
    fread(key, sizeof(unsigned int), 1, file);
    fread(rel, sizeof(unsigned int), 1, file);
}

static void download_else(FILE* file, int* offset, int* size){
    fread(offset, sizeof(unsigned int), 1, file);
    fread(size, sizeof(unsigned int), 1, file);
}

void print(Table* data){
    int l = 17;
    for (int i = 0; i < 10 + 10 + l + 1 + 1; i++){
        printf("_");
    }
    printf("\n");
    cap(l);
    printf("\n");

    int length = 0;
    fseek(data->file, data->password, SEEK_SET);
    fread(&length, sizeof(int), 1, data->file);

    unsigned int fkey, frel;
    int offset, len;

    for (int i = 0; i < length; i++){

        fseek(data->file, (long) sizeof(KeySpace) * i + data->start, SEEK_SET);
        download(data->file, &fkey, &frel);
        download_else(data->file, &offset, &len);

        char* string = calloc(len + 1, sizeof(char));
        fseek(data->str_file, offset, SEEK_SET);
        fread(string, sizeof(char), len, data->str_file);
        string[len] = '\0';

        line(l, ' ');
        printf("\n");
        print_info(fkey, frel, string, l);
        printf("\n");
        line(l, '_');
        printf("\n");
        free(string);
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
static void print_info(unsigned int key, unsigned int rel, char* string, int l){
    printf("| ");
    printf("%u", key);
    for (int i = 0; i < 8 - len_number(key); i++){
        printf(" ");
    }
    printf("| ");
    printf("%u", rel);
    for (int i = 0; i < 8 - len_number(rel); i++){
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
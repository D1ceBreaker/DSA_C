#include "user.h"
#define PASSWORD "password"

Table* Initialise(char* str_file){
    printf("Enter the file name:\n");
    char* f_main = readline();

    FILE* file = fopen(f_main, "rb+");
    if (file == NULL){
        file = fopen(f_main, "wb+");

        printf("File %s does not exist, creating new file...\n", f_main);
        printf("Enter the size of new table\n");
        int size = (int) getPosInt();

        fseek(file, 0, SEEK_SET);
        fwrite(PASSWORD, sizeof(char), 8, file);
        int len = 0;
        fwrite(&len, sizeof(int), 1, file);
        fwrite(&size, sizeof(int), 1, file);

        FILE* strs = fopen(str_file, "wb+");
        free(f_main);
        return open(file, strs);
    }
    else{
        char* buf = calloc(9, sizeof(char ));
        fread(buf, sizeof(char ), 8, file);
        free(f_main);

        if (strcmp(buf, PASSWORD) != 0){
            free(buf);
            printf("File format does not support tables\n");
            return NULL;
        }
        else{
            free(buf);
            FILE* strs = fopen(str_file, "rb+");
            printf("Success, table is ready\n");
            return open(file, strs);
        }

    }
}

void AddElement(Table* data){
    printf("Enter the key:\n");
    unsigned int key = getPosInt();
    printf("Enter the information:\n");
    scanf("%*c");
    char* info = readline();

    int res = add(data, key, info);
    if (res) printf("Table is full\n");
}

void Find(Table* data){
    printf("Enter the key:\n");
    unsigned int key = getPosInt();
    printf("Enter the release version | 0 if all:\n");
    unsigned int rel = getPosInt();

    FILE* result = fopen("found.bin", "wb+");
    Table* f = search(data, result, key, rel);
    print(f);

    fclose(result);
    free(f);
}

void Delete(Table* data){
    printf("Enter the key:\n");
    unsigned int key = getPosInt();
    printf("Enter the version | 0 if you need all releases\n");
    unsigned int rel = getPosInt();

    delete(data, key, rel);
}

void Upload(Table* data){
    printf("Enter the filename:\n");
    char* file = readline();
    scanf("%*c");
    FILE* f = fopen(file, "r");
    if (f == NULL){
        printf("Unable to open %s\n", file);
        return;
    }
    int len;
    char* s_len = readfile(f);
    len = (int)string_to_int(s_len);
    free(s_len);

    for (int i = 0; i < len; i++){
        unsigned int key;
        char* s_key = readfile(f);
        key = string_to_int(s_key);
        free(s_key);

        char* info = readfile(f);
        add(data, key, info);
    }
    free(file);
    fclose(f);
}

unsigned int getPosInt(){
    long long int num;
    int k = scanf("%lld", &num);
    while (k <= 0){
        scanf("%*c");
        k = scanf("%lld", &num);
    }
    if (num < 0) num = getPosInt();
    if (num > (long long int) UINT_MAX) num = getPosInt();
    return num;
}

char* readline(){
    //scanf("%*c");
    char* line = calloc(1, sizeof(char));
    int len = 0;
    int c = getchar();
    while (c != '\n'){
        len++;
        line = (char*) realloc(line, (len + 1) * sizeof(char));
        line[len - 1] = (char)c;
        line[len] = '\0';
        c = getchar();
    }
    return line;
}

char* readfile(FILE *file){
    char *input = calloc(1, sizeof (char));

    char buf[81] = {0};
    int flag = 1;
    int length = 0;
    int buf_len;
    while (flag > 0) {
        flag = fscanf(file, "%80[^\n]", buf);
        if (!flag)
            fscanf(file, "%*c");
        else {
            buf_len = strlen(buf);
            length += buf_len;
            input = realloc(input, length + 1);
            memcpy(input + length - buf_len, buf, buf_len * sizeof (char));
            input[length] = '\0';
        }
    }
    return input;
}

static unsigned int string_to_int(char *str){
    unsigned int result = 0;
    while (*str != '\0') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result;
}
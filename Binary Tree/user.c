#include "user.h"

void Add(Tree* data){
    printf("Enter the key:\n");
    scanf("%*c");
    char* key = readline();
    printf("Enter the value:\n");
    unsigned int value = getPosInt();
    add(data, key, value);
}

void Delete(Tree* data){
    printf("Enter the key:\n");
    scanf("%*c");
    char* key = readline();
    printf("Enter the release version:\n");
    unsigned int rel = getPosInt();
    delete(data, key, rel);
    free(key);
}

void Find(Tree* data){
    printf("Enter the key:\n");
    scanf("%*c");
    char* key = readline();
    Node* found = search(data->root, key);
    if (found){
        Info* ptr = found->list;
        printf("Key: %s | values: ", found->key);
        while (ptr){
            printf("%u ", ptr->value);
            ptr = ptr->next;
        }
        printf("\n");
    }
    else printf("This node does not exist\n");
    //free(key);
    free(found);
}

void SpecialSearch(Tree* data) {
    if (data->root == NULL) {
        printf("The tree is empty\n");
        return;
    }
    Node *found = findMin(data->root);
    if (found) {
        Info *ptr = found->list;
        printf("Key: %s | values: ", found->key);
        while (ptr) {
            printf("%d ", ptr->value);
            ptr = ptr->next;
        }
        printf("\n");
    }
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

char* readfile(FILE *file) {
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

static unsigned int string_to_int(char *str) {
    unsigned int result = 0;
    while (*str != '\0') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result;
}

int Upload(Tree * data){
    printf("Enter the filename:\n");
    char* file = readline();
    scanf("%*c");
    FILE* f = fopen(file, "r");
    if (f == NULL){
        return 1;
    }
    int len;
    char* s_len = readfile(f);
    len = (int)string_to_int(s_len);
    free(s_len);
    for (int i = 0; i < len; i++){
        unsigned int val;
        char* s_val = readfile(f);
        val = string_to_int(s_val);
        free(s_val);

        char* key = readfile(f);
        add(data, key, val);
    }
    free(file);
    fclose(f);
    return 0;
}
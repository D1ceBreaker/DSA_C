#include <stdio.h>
#include "dialog.h"
#include "table.h"
#include "user.h"
int main() {
    /*
    Table* data = create(5);
    data = push(data, 1, "aaaaaa");
    data = push(data, 1, "aaaaaa");
    data = push(data, 1, "aaaaaa");
    print(data);
    data = delete(data, 1, 1);
    for (int i = 0; i < data->len; i++){
        printf("%d ", data->keys[i]);
    }
    printf("\n");
    data = push(data, 1, "bbbbbb");
    print(data);
    for (int i = 0; i < data->len; i++){
        printf("%d ", data->keys[i]);
    }
    printf("\n");
     */
    char* a = readline();
    printf("%s", a);
    return 0;
}

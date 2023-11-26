#include "dialog.h"
#include <stdio.h>
#include "table.h"
int main() {
    int a;
    scanf("%d", &a);
    unsigned b = hash(a);
    printf("hash: %u\n", b);

    return 0;
}

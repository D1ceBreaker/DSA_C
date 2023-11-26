#ifndef USER_H
#define USER_H

#include "tree.h"

void Add(Splay* data);
void Find(Splay* data);
Splay* Delete(Splay* data);
void SpecialFind(Splay* data);
int Upload(Splay * data);

unsigned int getPosInt();
char* readline();
char* readfile(FILE *file);
static unsigned int string_to_int(char *str);

#endif //USER_H

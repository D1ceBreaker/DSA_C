
#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "tree.h"

void Add(Tree* data);
void Delete(Tree* data);
int Upload(Tree* data);
void Find(Tree* data);
void SpecialSearch(Tree* data);


unsigned int getPosInt();
char* readline();
char* readfile(FILE* file);

#endif //USER_H

#ifndef USER_H
#define USER_H

#include "table.h"
#include <string.h>

Table* Initialise(char* str_file);
void AddElement(Table* data);
void Find(Table* data);
void Delete(Table* data);
void Upload(Table* data);


unsigned int getPosInt();
char* readline();
char* readfile(FILE *file);
static unsigned int string_to_int(char *str);

#endif //USER_H

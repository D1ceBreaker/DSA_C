#ifndef USER_H
#define USER_H
#include "table.h"

Table* CreateTable();
Table* AddElement(Table* data);
void FindElements(Table* data);
Table* CompressTable(Table* data);
void Print(Table* data);
void Delete(Table* data);

unsigned int getPosInt();
static char* readline();

#endif //USER_H

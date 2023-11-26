
#ifndef USER_H
#define USER_H
#include "table.h"
Table* CreateTable();
Table* AddElement(Table* data);
Table* DeleteElement(Table* data);
void DeleteTable(Table* data);
int FindElement(Table* data);
char* readline();
int getPosInt();
char* readline2();
#endif //USER_H

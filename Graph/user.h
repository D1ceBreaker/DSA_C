#ifndef USER_H
#define USER_H

#include "graph.h"
void AddVertex(Graph* data);
void AddEdge(Graph* data);
void ChangeVertex(Graph* data);
void ChangeEdge(Graph* data);
void DeleteVertex(Graph* data);
void DeleteEdge(Graph* data);
void DepthSearch(Graph* data);
void ShortestPath(Graph* data);
Graph* MinSpan(Graph* data);

unsigned int getPosInt();
char* readline();
static unsigned* getPorts(unsigned len);

#endif //USER_H

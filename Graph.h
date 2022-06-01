#ifndef GRAPH
#define GRAPH
#include "limits.h"
#include "Matrix.h"
#include "List.h"
#define INF 10000
int MIN(int a, int b);
typedef struct {
	MatrixInteger* arcs;
	List* names;
} Graph;
// 29.05.2022
Graph* CallocGraph();
// 29.05.2022
void FreeGraph(Graph* graph);
// 29.05.2022
void InitGraph(Graph** graph);
// 29.05.2022
void PrintGraph(Graph* graph);
// 30.05.2022
Graph* CopyGraph(Graph* graph);
// 30.05.2022
int* InitArray(int n, int a);
#endif
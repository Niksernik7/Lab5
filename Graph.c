#include "Graph.h"
// 29.05.2022 ��������� ������ ��� ����
Graph* CallocGraph() {
	Graph* res = (Graph*)calloc(1, sizeof(Graph));
	res->arcs = (MatrixInteger*)CreateMatrixInteger(0, 0);
	res->names = (List*)list_new();
	return res;
}
// 30.05.2022 ����������� ����� 
Graph* CopyGraph(Graph* graph) {
	assert(graph != NULL);
	Graph* res = (Graph*)calloc(1, sizeof(Graph));
	res->arcs = (MatrixInteger*)CopyMatrixInteger(graph->arcs);
	return res;
}
// 29.05.2022 ������������ ����� 
void FreeGraph(Graph* graph) {
	if (graph == NULL)
		return;
	FreeMatrixInteger(graph->arcs);
	list_delete(graph->names);
	free(graph);
}
// 29.05.2022 ������ ����� 
void PrintGraph(Graph* graph) {
	if (graph == NULL) {
		printf("NULL\n");
		return;
	}
	printf("Is direct graph\n");
	MatrixIntegerPrintf(graph->arcs);
}
// 30.05.2022 ����������� ����� 
int MIN(int a, int b) {
	if (a < b)
		return a;
	return b;
}
// 30.05.2022 ���������������� ������
int* InitArray(int n, int a) {
	int* res = (int*)calloc(n, sizeof(int));
	if (res == NULL)
		return NULL;
	for (int i = 0; i < n; i++)
		res[i] = a;

	return res;
}

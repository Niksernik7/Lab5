
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "Queue.h"
#include "BFSTraverse.c"
#include "Dijkstra.c"
#include "Dinic.c"
#include "Ford-FulkersonAlgorithm.c"
// 31.05.2022 ����
typedef enum Menu {
	Show,
} Menu;
// 31.05.2022 ������ ����
typedef enum MenuTopics {
	BFsTraverseTopic = 6,
	DijkstraTopic = 7,
	FordFulkersonAlgorithmTopic = 8,
	ExitTopic = 0,
	InputFromConsole = 1,
	InputFromFileTopic = 2,
	PrintInputGraphTopic = 3,
	PrintOutputGraphTopic = 4,
	OutputGraphEquelInputGraphTopic = 5,
	SaveToFileGraphTopic = 9,
	SaveToFileGraph_resTopic = 10,
	addingVertexTopic = 11,
	addingEdgeTopic = 12, 
	deletingVertexTopic = 13,
	deletingEdgeTopic = 14,
} MenuTopics;

// 31.05.2022 ����������� �������� � �������������
void printVal(const char *string, int n) {
	printf("%s%d\n", string, n);
}
// 31.05.2022 �������� �� ����� 0 �� oo
int getNotNegativeNum() {
	int res = -1;
	while (res < 0) {
		printf("Input not negative number\n");
		scanf("%d", &res);
	}
	return res;
}
// 31.05.2022 �������� �� ����� 0 �� oo � ������������
int getNotNegativeNumWithComment(const char* comment) {
	printf("%s\n", comment);
	return getNotNegativeNum();
}
// 31.05.2022 �������� �� ����� 0 �� oo � ������������ � ������ ��������� ����� 
int getNotNegativeNotGreaterOrEquelThen(const char* comment, int n) {
	int res = -1;
	while (res < 0 || res >= n) {
		printf("Input number less then %d\n", n);
		res = getNotNegativeNumWithComment(comment);
	}
	return res;
}
// 31.05.2022 �������� ����� ������� �� ������������ 
int getVertex(Graph* graph, const char* comment) {
	return getNotNegativeNotGreaterOrEquelThen(comment, graph->arcs->ColumnCount);
}
// 31.05.2022 ����������� ���� ������ � ������ 
void printPathBFsTraverse(int* path, int n, int v1, int v2) {
	int i, j;
	for (i = 0; i < n; i++)
		if (path[i] == v1 || path[i] == v2)
			break;
	if (path[i] == v2)
		v2 = v1;
	for (j = i; j < n; j++)
		if (path[j] == v2)
			break;
	for (int k = i; k <= j; k++)
		printf("%d ", path[k]);
	printf("\n");
}
// 31.05.2022 ����� ���� �������� � ����� 
void FindPathWithBFsTraverse(Graph* graph) {
	assert(graph != NULL);
	int v1 = getVertex(graph, "Input start vertex");
	int v2 = getVertex(graph, "Input finish vertex");
	int* path = BethFirstSearchTraverse(graph);
	printPathBFsTraverse(path, graph->arcs->ColumnCount, v1, v2);
	free(path);
}
// 31.05.2022 ������ ����
void printMainMenu() {
	printf("***Directed graphs, weights is not negative***\n");
	printf("0) Quit\n");
	printf("1) Input from console\n");
	printf("2) Input from file\n");
	printf("3) Print input graph\n");
	printf("4) Print output graph\n");
	printf("5) Output graph = input graph\n");
	printf("6) Finding some given vertex from another given vertex by breadth-first search\n");
	printf("7) Finding the shortest path between two given vertices\n");
	printf("8) construction of the residual network at the maximum flow between \
two given vertices\n");
	printf("9) Save to file graph\n");
	printf("10) Save to file graph_res\n");
	printf("11) adding a new vertex\n");
	printf("12) adding a new edge between two given vertices\n");
	printf("13) deleting a given vertex\n");
	printf("14) deleting a given edge\n");
}
// 31.05.2022
void PrintArrayWithout(int* arr, int n, int without) {
    for (int i = 0; i < n; i++)
        if (arr[i] != without)
            printf("%d ", arr[i]);
}
// 31.05.2022 ����� ����������� ���� ����� ������ 
void FindPathDijkstra(Graph* graph) {
	assert(graph != NULL);
	int v1 = getVertex(graph, "Input start vertex");
	int v2 = getVertex(graph, "Input finish vertex");
	int* path = Dijkstra(graph, v1, v2);
	printf("Path: ");
	PrintArrayWithout(path, graph->arcs->ColumnCount, -1);
	printf("\n");
	free(path);
}
// 31.05.2022 FordFulkersonAlgorithm
Graph *FordFulkersonAlgorithmMenu(Graph* graph) {
	assert(graph != NULL);
	Graph* res = (Graph*)CallocGraph();
	FreeMatrixInteger(res->arcs);
	int source = getVertex(graph, "Input start source");
	int sink = getVertex(graph, "Input finish sink");
	fordFulkersonRes* ffres = fordFulkerson(graph, source, sink);
	ffres = GetResidualGraph(graph, ffres);
	printf("ResidualGraph: \n");
	MatrixIntegerPrintf(ffres->mi);
	printf("\n");
	printVal("MaxFlow = \n", ffres->max_flow);
	res->arcs = ffres->mi;
	free(ffres);
	return res;
}
// 31.05.2022 ������� ���� 
Graph* GraphFread() {
	char str[128];
	printf("Input file name: ");
	scanf("%s", str);
	Graph* res = CallocGraph();
	FreeMatrixInteger(res->arcs);
	res->arcs = (MatrixInteger*)MatrixIntegerFread(str);
	return res;
}
// 31.05.2022 ��������� ���� � ���� 
void GraphFwrite(Graph *graph) {
	assert(graph != NULL);
	char str[128];
	printf("Input file name: ");
	scanf("%s", str);
	MatrixIntegerFwrite(graph->arcs, str);
}
// 31.05.2022 �������� ������� 
void addingVertex(Graph *graph) {
	assert(graph != NULL);
	int n = graph->arcs->ColumnCount, v1_index, v2_index, w;
	int arcsCount = getNotNegativeNumWithComment("Input count of arcs: ");
	int* column = (int*)InitArray(n, 0);
	int* row = (int*)InitArray(n + 1, 0);
	for (int i = 0; i < arcsCount; i++)
	{
		do {
			printf("Input arc\n");
			printf("Input i:");
			scanf("%d", &v1_index);
			printf("Input j:");
			scanf("%d", &v2_index);
			printf("Input weight:");
			scanf("%d", &w);
		} while (!((v1_index < n && v2_index == n) || (v1_index == n)));
		if (v1_index == n)
			row[v2_index] = w;
		else
			column[v1_index] = w;
	}
	MatrixInteger* buf = graph->arcs;
	graph->arcs = (MatrixInteger*)CreateMatrixInteger(n + 1, n + 1);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			graph->arcs->Rows[i][j] = buf->Rows[i][j];
	for (int j = 0; j < n + 1; j++)
		graph->arcs->Rows[n][j] = row[j];
	for (int i = 0; i < n; i++)
		graph->arcs->Rows[i][n] = column[i];
	free(row);
	free(column);
	FreeMatrixInteger(buf);
}
// 31.05.2022 �������� ����� 
void addingEdge(Graph* graph) {
	assert(graph != NULL);
	int v1 = getVertex(graph, "Input start vertex");
	int v2 = getVertex(graph, "Input finish vertex");
	int w = getNotNegativeNumWithComment("Input weight");
	graph->arcs->Rows[v1][v2] = w;
}
// 31.05.2022 ������� ������� 
void deletingVertex(Graph* graph) {
	assert(graph != NULL);
	int v1 = getVertex(graph, "Input vertex for delete");
	MatrixInteger* buf = graph->arcs;
	graph->arcs = EraseColumnMatrixInteger(graph->arcs, v1);
	FreeMatrixInteger(buf);
	buf = graph->arcs;
	graph->arcs = EraseRowMatrixInteger(graph->arcs, v1);
	FreeMatrixInteger(buf);
}
// 31.05.2022 ������� �����
void deletingEdge(Graph* graph) {
	assert(graph != NULL);
	int v1 = getVertex(graph, "Input start vertex");
	int v2 = getVertex(graph, "Input finish vertex");
	graph->arcs->Rows[v1][v2] = 0;
}
// 31.05.2022 ����� enter
void WaitForEnter(const char *mesg) {
	printf("%s\n", mesg);
	scanf("%*c");
	scanf("%*c");
}
// 29.05.2022
void InitGraph(Graph **graph) {
	int vexcount, arccount, v1_index, v2_index, weight;
	FreeGraph(*graph);
	*graph = (Graph*)CallocGraph();
	vexcount = getNotNegativeNumWithComment("Input count of vexes");
	arccount = getNotNegativeNotGreaterOrEquelThen("Input count of arcs", vexcount * (vexcount - 1));
	FreeMatrixInteger((*graph)->arcs);
	(*graph)->arcs = (MatrixInteger*)CreateMatrixInteger(vexcount, vexcount);
	for (int i = 0; i < arccount; i++) {
		printf("Input arc\n");
		v1_index = getNotNegativeNotGreaterOrEquelThen("Input i - index of start vex", vexcount);
		v2_index = getNotNegativeNotGreaterOrEquelThen("Input j - index of finish vex", vexcount);
		weight = getNotNegativeNumWithComment("Input weight");
		(*graph)->arcs->Rows[v1_index][v2_index] = weight;
	}
}
// 31.05.2022 ������ �������� ����
void MainMenu() {
	Graph* graph_res = NULL;
	Graph* graph = NULL;
	Menu menu = Show;
	int userInput = -1;
	while (menu == Show) {
		printMainMenu();
		userInput = getNotNegativeNum();
		switch (userInput)
		{
		case BFsTraverseTopic:
			FindPathWithBFsTraverse(graph);
			WaitForEnter("FindPathWithBFsTraverse success");
			break;
		case DijkstraTopic:
			FindPathDijkstra(graph);
			WaitForEnter("FindPathDijkstra success");
			break;
		case FordFulkersonAlgorithmTopic:
			FreeGraph(graph_res);
			graph_res = NULL;
			graph_res = FordFulkersonAlgorithmMenu(graph);
			WaitForEnter("FordFulkersonAlgorithm success");
			break;
		case ExitTopic:
			menu = 1;
			WaitForEnter("Exit success");
			break;
		case InputFromConsole:
			FreeGraph(graph);
			graph = NULL;
			InitGraph(&graph);
			WaitForEnter("InputFromConsole success");
			break;
		case InputFromFileTopic:
			FreeGraph(graph);
			graph = NULL;
			graph = GraphFread();
			WaitForEnter("InputFromFile success");
			break;
		case PrintInputGraphTopic:
			PrintGraph(graph);
			WaitForEnter("PrintGraph success");
			break;
		case PrintOutputGraphTopic:
			PrintGraph(graph_res);
			WaitForEnter("PrintGraph success");
			break;
		case OutputGraphEquelInputGraphTopic:
			FreeGraph(graph_res);
			graph_res = NULL;
			graph_res = CopyGraph(graph);
			WaitForEnter("OutputGraphEquelInputGraph success");
			break;
		case SaveToFileGraphTopic:
			GraphFwrite(graph);
			WaitForEnter("GraphFwrite(graph) success");
			break;
		case SaveToFileGraph_resTopic:
			GraphFwrite(graph_res);
			WaitForEnter("GraphFwrite(graph_res) success");
			break;
		case addingVertexTopic:
			addingVertex(graph);
			WaitForEnter("addingVertex success");
			break;
		case addingEdgeTopic:
			addingEdge(graph);
			WaitForEnter("addingEdgeTopic success");
			break;
		case deletingVertexTopic:
			deletingVertex(graph);
			WaitForEnter("deletingVertex success");
			break;
		case deletingEdgeTopic:
			deletingEdge(graph);
			WaitForEnter("deletingEdge success");
			break;
		default:
			break;
		}
	}
	FreeGraph(graph);
}
// 31.05.2022 Main
int main() {
	MainMenu();
	return 0;
}
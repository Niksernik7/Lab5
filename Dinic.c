#include "Graph.h"
#include "List.h"
// 31.05.2022 ����� � �������
int dfs(int v, int flow, int** c, int** f, int s, int t, int* d, int* ptr, int* q, int n) {
	if (!flow)  return 0;
	if (v == t)  return flow;
	for (int to = ptr[v]; to < n; ++to) {
		if (d[to] != d[v] + 1)  continue;
		int pushed = dfs(to, MIN(flow, c[v][to] - f[v][to]), c, f, s, t, d, ptr, q, n);
		if (pushed) {
			f[v][to] += pushed;
			f[to][v] -= pushed;
			return pushed;
		}
	}
	return 0;
}
// 31.05.2022 ����� � ������
int bfs(int** c, int** f, int s, int t, int* d, int* ptr, int* q, int n) {
	int qh = 0, qt = 0;
	q[qt++] = s;
	memset(d, -1, n * sizeof d[0]);
	d[s] = 0;
	while (qh < qt) {
		int v = q[qh++];
		for (int to = 0; to < n; ++to)
			if (d[to] == -1 && f[v][to] < c[v][to]) {
				q[qt++] = to;
				d[to] = d[v] + 1;
			}
	}
	return d[t] != -1;
}
// 31.05.2022 �������� ������
int dinic(Graph *graph, int start, int finish) {
	assert(graph != NULL);
	int flow_in_web = 0;
	int** c = graph->arcs->Rows;
	int n = graph->arcs->ColumnCount;
	MatrixInteger* f_mi = (MatrixInteger*)CreateMatrixInteger(n, n);
	int** f = f_mi->Rows;
	int* d = InitArray(n, 0);
	int* ptr = InitArray(n, 0);
	int* q = InitArray(n, 0);
	while(1) {
		if (!bfs(c, f, start, finish, d, ptr, q, n))  
			break;
		memset(ptr, 0, n * sizeof ptr[0]);
		int pushed;
		do {
			pushed = dfs(start, INF, c, f, start, finish, d, ptr, q, n);
			flow_in_web += pushed;
		} while (pushed);
	}
	FreeMatrixInteger(f_mi);
	free(d);
	free(ptr);
	free(q);
	return flow_in_web;
}

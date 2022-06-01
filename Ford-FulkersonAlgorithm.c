#include <stdio.h>
#include "Graph.h"
#define A 0
#define B 1
#define C 2
// 31.05.2022 ����� � ������
int bfs_f(int start, int target, int n, int* color, int** capacity, int** flow, int* pred) {
    Queue* queue = (Queue*)InitQueue();
    int u, v;
    for (u = 0; u < n; u++) {
        color[u] = A;
    }
    QueueIn(queue, start);
    color[start] = B;
    pred[start] = -1;
    while(!Empty(queue)) {
        u = QueueOut(queue);
        color[u] = C;
        for (v = 0; v < n; v++) {
            if (color[v] == A && capacity[u][v] - flow[u][v] > 0) {
                QueueIn(queue, v);
                color[v] = B;
                pred[v] = u;
            }
        }
    }
    return color[target] == C;
}
// 31.05.2022 ��������� ��������� 
typedef struct fordFulkersonRes {
    MatrixInteger* mi;
    int max_flow;
} fordFulkersonRes;
// 31.05.2022 ��������� ResidualGraph
fordFulkersonRes* GetResidualGraph(Graph* graph, fordFulkersonRes* flow_res) {
    assert(flow_res != NULL);
    MatrixInteger* copy = (MatrixInteger*)CopyMatrixInteger(graph->arcs);
    int n = graph->arcs->ColumnCount;
    int dif = 0;
    for (int i = 0; i < copy->ColumnCount; i++) {
        dif = 0;
        for (int j = 0; j < copy->ColumnCount; j++)
            if (copy->Rows[i][j] != flow_res->mi->Rows[i][j])
                dif = 1;
        if (dif == 0) {
            MatrixInteger *buf = copy;
            copy = EraseColumnMatrixInteger(copy, i);
            FreeMatrixInteger(buf);
            buf = copy;
            copy = EraseRowMatrixInteger(copy, i);
            FreeMatrixInteger(buf);
            buf = flow_res->mi;
            flow_res->mi = EraseColumnMatrixInteger(flow_res->mi, i);
            FreeMatrixInteger(buf);
            buf = flow_res->mi;
            flow_res->mi = EraseRowMatrixInteger(flow_res->mi, i);
            FreeMatrixInteger(buf);
            i--;
        }
    }
    FreeMatrixInteger(flow_res->mi);
    flow_res->mi = copy;
    return flow_res;
}
// 31.05.2022 �������� fordFulkerson
fordFulkersonRes *fordFulkerson(Graph *graph, int source, int sink) {
    assert(graph != NULL);
    int n = graph->arcs->ColumnCount;
    int **capacity = graph->arcs->Rows;
    MatrixInteger* flow_mi = (MatrixInteger*)CreateMatrixInteger(n, n);
    int **flow = flow_mi->Rows;
    int *color = (int*)InitArray(n, 0);
    int *pred = (int*)InitArray(n, 0);
    int i, j, u;
    int max_flow = 0;
    int* q = (int*)InitArray(n + 2, 0);
    while (bfs_f(source, sink, n, color, capacity, flow, pred)) {
        int increment = INF;
        for (u = n - 1; pred[u] >= 0; u = pred[u]) {
            increment = MIN(increment, capacity[pred[u]][u] - flow[pred[u]][u]);
        }
        for (u = n - 1; pred[u] >= 0; u = pred[u]) {
            flow[pred[u]][u] += increment;
            flow[u][pred[u]] -= increment;
        }
        max_flow += increment;
    }
    free(q);
    free(color);
    free(pred);
    fordFulkersonRes* res = (fordFulkersonRes*)calloc(1, sizeof(fordFulkersonRes));
    res->mi = flow_mi;
    res->max_flow = max_flow;
    return res;
}

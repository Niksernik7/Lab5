#include "Graph.h"
// 31.05.2022 �������� ��������
int *Dijkstra(Graph* graph, int begin_index, int end) {
    assert(graph != NULL);
    int SIZE = graph->arcs->ColumnCount;
    int** a = graph->arcs->Rows;
    int* d = (int*)InitArray(SIZE, INF);
    int* v = (int*)InitArray(SIZE, 1);
    int temp, minindex, min;
    d[begin_index] = 0;
    do {
        minindex = INF;
        min = INF;
        for (int i = 0; i < SIZE; i++)
            if ((v[i] == 1) && (d[i] < min))
            { 
                min = d[i];
                minindex = i;
            }
        if (minindex != INF)
        {
            for (int i = 0; i < SIZE; i++)
            {
                if (a[minindex][i] > 0)
                {
                    temp = min + a[minindex][i];
                    if (temp < d[i])
                    {
                        d[i] = temp;
                    }
                }
            }
            v[minindex] = 0;
        }
    } while (minindex < INF);
    int* ver = (int*)InitArray(graph->arcs->ColumnCount, -1);
    end -= 1;
    ver[0] = end + 1; 
    int weight = d[end];
    int k = 1; 
    while (end != begin_index) 
        for (int i = 0; i < SIZE; i++)
            if (a[i][end] != 0)   
            {
                int temp = weight - a[i][end]; 
                if (temp == d[i]) 
                {                 
                    weight = temp; 
                    end = i;       
                    ver[k] = i + 1; 
                    k++;
                }
            }
    printf("\nShortest distances at all vertexs: \n");
    for (int i = 0; i < SIZE; i++)
        printf("%d ", d[i]);
    printf("\n");
    free(d);
    free(v);
    return ver;
}

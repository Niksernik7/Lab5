#include "Graph.h"
#include "Queue.h"
// 31.05.2022 ����� � ������
int *BethFirstSearchTraverse(Graph *graph) {
	Queue* queue = (Queue*)InitQueue();
	int countOfVexes = graph->arcs->ColumnCount;
	int *visited = (int*)InitArray(countOfVexes, 0);
	int* res = (int*)InitArray(countOfVexes, 0);
	int k = 0;
	int i = 0, j, v = 0;
	do {
		if (!visited[i])
		{
			res[k] = i;
			k++;
			visited[i] = 1;
			QueueIn(queue, i);

			while (Empty(queue))
			{
				v = QueueOut(queue);
				for (j = 0; j < countOfVexes; j++)
					if (graph->arcs->Rows[i][j] == 1 && visited[j] != 1)
					{
						res[k] = j;
						k++;
						visited[j] = 1;
						QueueIn(queue, j);
					}
			}
		}
		i++;
	} while (i < countOfVexes);
	free(visited);
	return res;
}

#ifndef QUEUE
#define QUEUE
#include "List.h"
// 30.05.2022
typedef struct Queue {
	List* sequ;
	int  len;
} Queue;
// 29.05.2022
Queue* InitQueue();
// 29.05.2022
void QueueIn(Queue* queue, int x);
// 29.05.2022
int QueueOut(Queue* queue);
// 29.05.2022
int Empty(Queue* sq);
#endif

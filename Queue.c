#include "Queue.h"
// 29.05.2022
Queue* InitQueue() {
	Queue* sq = (Queue*)calloc(1, sizeof(Queue));
	sq->sequ = list_new();
	return sq;
}
// 29.05.2022
void QueueIn(Queue* queue, int x) {
	assert(queue != NULL);
	queue->len++;
	list_push_back(queue->sequ, x);
}
// 29.05.2022
int QueueOut(Queue* queue) {
	assert(queue != NULL);
	queue->len--;
	return list_pop_front(queue->sequ);
}
// 29.05.2022
int Empty(Queue* sq) {
	if (sq == NULL || sq->len == 0)
		return 1;
	return 0;
}

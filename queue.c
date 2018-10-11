// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#include <stdlib.h>

#include "queue.h"

Queue * createStringQueue(int capacity) {
	Queue* queue;
	queue = (Queue*) malloc(sizeof(Queue));
	queue->elements = (char**) malloc(capacity * sizeof(char*));
	queue->first = 0;
	queue->last = 0;
	return queue;
}

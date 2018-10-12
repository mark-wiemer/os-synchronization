// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#include <pthread.h>
#include <stdlib.h>

#include "queue.h"

Queue * createStringQueue(int capacity) {
	Queue* queue;

	queue = (Queue*) malloc(sizeof(Queue));
	pthread_mutex_init(&(queue->mutex), NULL); // initialize with default values
	queue->elements = (char**) malloc(capacity * sizeof(char*));
	queue->capacity = capacity;
	queue->first = 0;
	queue->last = 0;

	return queue;
}

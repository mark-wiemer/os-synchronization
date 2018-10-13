// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#include <pthread.h>
#include <stdlib.h>

#include "queue.h"

Queue * createStringQueue(int capacity) {
	Queue* q;

	q = (Queue*) malloc(sizeof(Queue));
	pthread_mutex_init(&(q->mutex), NULL); // initialize with default values
	pthread_cond_init(&(q->empty), NULL); // TODO error handling?
	pthread_cond_init(&(q->full), NULL); // TODO error handling?
	q->elements = (char**) malloc(capacity * sizeof(char*));
	q->capacity = capacity;
	q->first = 0;
	q->last = 0;

	return q;
}

void enqueueString(Queue *q, char *string) {
	pthread_mutex_lock(&(q->mutex));

	pthread_mutex_unlock(&(q->mutex));
	return;
}

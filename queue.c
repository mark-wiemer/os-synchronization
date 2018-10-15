// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "queue.h"

/** capacity is the max number of elements */
Queue * createStringQueue(int capacity) {
	Queue* q;

	q = (Queue*) malloc(sizeof(Queue));
	pthread_mutex_init(&(q->mutex), NULL); // initialize with default values
	pthread_cond_init(&(q->empty), NULL); // TODO error handling?
	pthread_cond_init(&(q->full), NULL); // TODO error handling?
	q->elements = (char**) malloc(capacity * sizeof(char*));
	for (int i = 0; i < capacity; i++) {
		q->elements[i] = (char*) malloc((buffsize() + 1) * sizeof(char));
	}
	q->capacity = capacity;
	q->first = 0;
	q->last = 0;

	q->enqueueCount = 0;
	q->dequeueCount = 0;

	return q;
}

void enqueueString(Queue *q, char *string) {
	pthread_mutex_lock(&(q->mutex));

	while (modIncrement(q, q->last) == q->first) { // while full
		pthread_cond_wait(&(q->full), &(q->mutex));
	}

	strcpy(q->elements[q->last], string);
	q->last = modIncrement(q, q->last);
	pthread_cond_signal(&(q->empty));

	q->enqueueCount++;

	pthread_mutex_unlock(&(q->mutex));
}

char * dequeueString(Queue *q) {
	char *string = (char*) malloc((buffsize() + 1) * sizeof(char));
	pthread_mutex_lock(&(q->mutex));

	while (q->first == q->last) { // while empty
		pthread_cond_wait(&(q->empty), &(q->mutex));
	}

	strcpy(string, q->elements[q->first]);
	q->first = modIncrement(q, q->first);
	pthread_cond_signal(&(q->full));

	q->dequeueCount++;

	pthread_mutex_unlock(&(q->mutex));
	return string;
}

int modIncrement(Queue *q, int index) {
	return (index + 1) % (q->capacity);
}


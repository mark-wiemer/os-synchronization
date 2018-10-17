// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "queue.h"

static const int MSG_LENGTH = 256;

/** capacity is the max number of elements */
Queue * createStringQueue(int capacity) {
	Queue* q;
	int error = 0;

	q = (Queue*) malloc(sizeof(Queue));
	if (q == NULL) {
		printf("malloc failed\n");
		return NULL;
	}
	if ((error = pthread_mutex_init(&(q->mutex), NULL))) { // initialize with default values
		printf("pthread_mutex_init failed with error code %d. Exiting...\n", error);
		return NULL;
	}
	if ((error = pthread_cond_init(&(q->empty), NULL))) {
		printf("pthread_cond_init 1 failed with error code %d. Exiting...\n", error);
		return NULL;
	}
	if ((error = pthread_cond_init(&(q->full), NULL))) {
		printf("pthread_cond_init 2 failed with error code %d. Exiting...\n", error);
		return NULL;
	}
	q->elements = (char**) malloc(capacity * sizeof(char*));
	if (q->elements == NULL) {
		printf("malloc 2 failed\n");
		return NULL;
	}

	q->capacity = capacity;
	q->first = 0;
	q->last = 0;

	q->enqueueCount = 0;
	q->dequeueCount = 0;
	q->enqueueBlockCount = 0;
	q->dequeueBlockCount = 0;

	return q;
}

void enqueueString(Queue *q, char *string) {
	pthread_mutex_lock(&(q->mutex));

	while (modIncrement(q, q->last) == q->first) { // while full
		q->enqueueBlockCount++;
		pthread_cond_wait(&(q->full), &(q->mutex));
	}

	q->elements[q->last] = string;

	q->last = modIncrement(q, q->last);
	pthread_cond_signal(&(q->empty));

	q->enqueueCount++;

	pthread_mutex_unlock(&(q->mutex));
}

char * dequeueString(Queue *q) {
	char *string;
	pthread_mutex_lock(&(q->mutex));

	while (q->first == q->last) { // while empty
		q->dequeueBlockCount++;
		pthread_cond_wait(&(q->empty), &(q->mutex));
	}

	if (q->elements[q->first] != NULL) {
		string = q->elements[q->first];
	} else {
		string = NULL;
	}

	q->first = modIncrement(q, q->first);
	pthread_cond_signal(&(q->full));

	q->dequeueCount++;

	pthread_mutex_unlock(&(q->mutex));
	return string;
}

int dequeueCount(Queue* q) {
	return q->dequeueCount;
}

int modIncrement(Queue *q, int index) {
	return (index + 1) % (q->capacity);
}

void printQueueInfo(Queue* q, char* name) {
	char msg[MSG_LENGTH];
	strcpy(msg, "%s:\n");
	strcat(msg, "\tenqueueCount: %d\n");
	strcat(msg, "\tdequeueCount: %d\n");
	strcat(msg, "\tenqueueBlockCount: %d\n");
	strcat(msg, "\tdequeueBlockCount: %d\n");
	printf(msg,
		name,
		q->enqueueCount,
		q->dequeueCount,
		q->enqueueBlockCount,
		q->dequeueBlockCount);
}


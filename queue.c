// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "queue.h"

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
	for (int i = 0; i < capacity; i++) {
		q->elements[i] = (char*) malloc(BUFFSIZE * sizeof(char));
		if (q->elements[i] == NULL) {
			printf("malloc index %d failed\n", i);
			return NULL;
		}
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

	if (string != NULL) {
		strcpy(q->elements[q->last], string);
	} else {
		q->elements[q->last] = NULL;
	}

	q->last = modIncrement(q, q->last);
	pthread_cond_signal(&(q->empty));

	q->enqueueCount++;

	pthread_mutex_unlock(&(q->mutex));
}

char * dequeueString(Queue *q) {
<<<<<<< HEAD
	char *string = (char*) malloc((buffsize() + 1) * sizeof(char));
		if (string == NULL) {
			printf("malloc string failed");
			return NULL;
		}

=======
	char *string = (char*) malloc(BUFFSIZE * sizeof(char));
>>>>>>> 20567b1e1ca1aa191efcee51d5a755ea2cc13196
	pthread_mutex_lock(&(q->mutex));

	while (q->first == q->last) { // while empty
		q->dequeueBlockCount++;
		pthread_cond_wait(&(q->empty), &(q->mutex));
	}

	if (q->elements[q->first] != NULL) {
		strcpy(string, q->elements[q->first]);
	} else {
		string = NULL;
	}

	q->first = modIncrement(q, q->first);
	pthread_cond_signal(&(q->full));

	q->dequeueCount++;

	pthread_mutex_unlock(&(q->mutex));
	return string;
}

int modIncrement(Queue *q, int index) {
	return (index + 1) % (q->capacity);
}


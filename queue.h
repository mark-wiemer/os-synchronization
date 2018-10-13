// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#ifndef QUEUE_H
#define QUEUE_H
typedef struct Queue {
	pthread_mutex_t mutex;
	pthread_cond_t empty;
	pthread_cond_t full;
	char **elements;
	int capacity;
	int first;
	int last;
} Queue;
Queue *createStringQueue(int capacity);
void enqueueString(Queue *queue, char *string);
#endif

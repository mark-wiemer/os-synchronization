// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#ifndef QUEUE_H
#define QUEUE_H
typedef struct Queue {
	char **elements;
} Queue;
Queue *createStringQueue(int capacity);
#endif

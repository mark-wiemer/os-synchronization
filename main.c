// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#include <pthread.h>
#include <stdio.h>

#include "queue.h"

#define CAPACITY 10
#define DEBUG 1

int main() {
	// Create the threads
	pthread_t reader_t;

	// Create the queues
	Queue *queue = createStringQueue(CAPACITY);

	// Start the threads

	// Wait for the threads to terminate

	if (DEBUG) printf("Capacity: %d, First: %d, Last: %d\n",
					queue->capacity,
					queue->first,
					queue->last);

	return 0;
}

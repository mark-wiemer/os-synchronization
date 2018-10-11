// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#include <pthread.h>

#include "queue.h"

#define CAPACITY 10

int main() {
	// Create the threads
	pthread_t reader_t;

	// Create the queues
	Queue *queue = createStringQueue(CAPACITY);

	// Start the threads

	// Wait for the threads to terminate

	return 0;
}

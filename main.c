// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#include <pthread.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "queue.h"
#include "reader.h"

#define BUFFSIZE 255
#define CAPACITY 10
#define DEBUG 1

/** global getter */
int buffsize() { return BUFFSIZE; }

/** Prints a fail message and returns count + 1 */
int fail(char *msg, int actual, int expected, int count) {
	fprintf(stderr, "ERROR %s: expected %d, got %d\n", msg, expected, actual);
	return count + 1;
}

int testModIncrement() {
	int error = 0; // falsy iff no error
	int actual;
	int expected;
	Queue *q = createStringQueue(CAPACITY);

	if ((actual = modIncrement(q, 0)) != (expected = 1)) {
		error = fail("modIncrement(q, 0)", actual, expected, error);
	}

	if ((actual = modIncrement(q, CAPACITY - 1)) != (expected = 0)) {
		error = fail("modIncrement(q, CAPACITY - 1)",  actual, expected, error);
	}

	return error;
}

int test() {
	int error = 0;
	error = testModIncrement();
	read();
	return error;
}

int main() {
	int error = test();

	// Create the threads
	// pthread_t reader_t;

	// Create the queues
	Queue *q = createStringQueue(CAPACITY);
	enqueueString(q, "Hello, world!");
	char msg[buffsize() + 1];

	strcpy(msg, dequeueString(q));

	// Start the threads

	// Wait for the threads to terminate

	return error;
}


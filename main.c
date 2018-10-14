// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#include <pthread.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "queue.h"
#include "reader.h"

#define BUFFSIZE 8	// TODO : change back to 256
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
	return error;
}

int main() {
	int error = test();
	char line[BUFFSIZE];

	// Create the threads
	pthread_t reader_t;

	// Create the queues
	Queue *readMunch1 = createStringQueue(CAPACITY);

	// Start the threads
	pthread_create(&reader_t, NULL, read, (void *)readMunch1);

	// Wait for the threads to terminate
	pthread_join(reader_t, NULL);

	while (readMunch1->first != readMunch1->last) { // not empty
		strcpy(line, dequeueString(readMunch1));
		printf("%s\n", line);
	}

	return error;
}


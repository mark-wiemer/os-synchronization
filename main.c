// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "munch.h"
#include "queue.h"
#include "reader.h"

#define BUFFSIZE 8	// TODO : change back to 256
#define CAPACITY 10
#define DEBUG 1
#define END_OF_THREAD ":)" // Some unique string to symbolize end of thread

/** global getter */
int buffsize() { return BUFFSIZE; }

char* eot() { return END_OF_THREAD; }

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
	pthread_t munch1_t;
	pthread_t munch2_t;

	// Create the queues
	Queue *read_munch1 = createStringQueue(CAPACITY);
	Queue *munch1_munch2 = createStringQueue(CAPACITY);
	Queue *munch2_write = createStringQueue(CAPACITY);

	MunchArgs *munch1Args = (MunchArgs*) malloc(sizeof(MunchArgs));
	munch1Args->in = read_munch1;
	munch1Args->out = munch1_munch2;

	MunchArgs *munch2Args = (MunchArgs*) malloc(sizeof(MunchArgs));
	munch2Args->in = munch1_munch2;
	munch2Args->out = munch2_write;

	// Start the threads
	pthread_create(&reader_t, NULL, read, (void*) read_munch1);
	pthread_create(&munch1_t, NULL, munch1, (void*) munch1Args);
	pthread_create(&munch2_t, NULL, munch2, (void*) munch2Args);


	// Wait for the threads to terminate
	pthread_join(reader_t, NULL);
	pthread_join(munch1_t, NULL);
	pthread_join(munch2_t, NULL);

	while (munch1_munch2->first != munch1_munch2->last) { // not empty
		strcpy(line, dequeueString(munch1_munch2));
		printf("%s\n", line);
	}

	return error;
}


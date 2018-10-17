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
#include "writer.h"

/** global getter */
const int BUFFSIZE = 1024;

static const int CAPACITY = 10;

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
	if (q == NULL) return 1;

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
	if (error) {
		fprintf(stderr, "ERROR: tests failed, quitting...\n");
		return error;
	}

	// Create the threads
	pthread_t reader_t;
	pthread_t munch1_t;
	pthread_t munch2_t;
	pthread_t writer_t;

	// Create the queues
	Queue *read_munch1 = createStringQueue(CAPACITY);
	if (read_munch1 == NULL) {
		fprintf(stderr, "read_munch1 initialization failed, quitting...\n");
		return 1;
	}
	Queue *munch1_munch2 = createStringQueue(CAPACITY);
	if (munch1_munch2 == NULL) {
		fprintf(stderr, "munch1_munch2 initialization failed, quitting...\n");
		return 1;
	}
	Queue *munch2_write = createStringQueue(CAPACITY);
	if (munch2_write == NULL) {
		fprintf(stderr, "munch2_write initialization failed, quitting...\n");
		return 1;
	}

	// Create the args
	MunchArgs *munch1Args = (MunchArgs*) malloc(sizeof(MunchArgs));
	if (munch1Args == NULL) {
		fprintf(stderr, "munch1Args initialization falied, quitting...\n");
		return 1;
	}
	munch1Args->in = read_munch1;
	munch1Args->out = munch1_munch2;

	MunchArgs *munch2Args = (MunchArgs*) malloc(sizeof(MunchArgs));
	if (munch2Args == NULL) {
		fprintf(stderr, "munch2Args initialization falied, quitting...\n");
		return 1;
	}
	munch2Args->in = munch1_munch2;
	munch2Args->out = munch2_write;

	// Start the threads
	if((error = pthread_create(&reader_t, NULL, read, (void*) read_munch1))) {
		fprintf(stderr, "reader thread creation failed, quitting...\n");
		return error;
	}
	if((error = pthread_create(&munch1_t, NULL, munch1, (void*) munch1Args))) {
		fprintf(stderr, "munch1 thread creation failed, quitting...\n");
		return error;
	}
	if ((error = pthread_create(&munch2_t, NULL, munch2, (void*) munch2Args))) {
		fprintf(stderr, "munch2 thread creation failed, quitting...\n");
		return error;
	}
	if ((error = pthread_create(&writer_t, NULL, write, (void*) munch2_write))) {
		fprintf(stderr, "writer thread creation failed, quitting...\n");
		return error;
	}

	// Wait for the threads to terminate
	if ((error = pthread_join(reader_t, NULL))) {
		fprintf(stderr, "reader thread joining failed, quitting...\n");
		return error;
	}
	if ((error = pthread_join(munch1_t, NULL))) {
		fprintf(stderr, "munch1 thread joining failed, quitting...\n");
		return error;
	}
	if ((error = pthread_join(munch2_t, NULL))) {
		fprintf(stderr, "munch2 thread joining failed, quitting...\n");
		return error;
	}
	if ((error = pthread_join(writer_t, NULL))) {
		fprintf(stderr, "writer thread joining failed, quitting...\n");
		return error;
	}

	// Print results
	printQueueInfo(read_munch1, "Reader to Munch1");
	printQueueInfo(munch1_munch2, "Munch1 to Munch2");
	printQueueInfo(munch2_write, "Munch2 to Writer");

	return 0;
}


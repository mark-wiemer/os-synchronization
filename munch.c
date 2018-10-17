// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "munch.h"

/** Convert spaces to asterisks */
void* munch1(void * queues) {
	MunchArgs* args = (MunchArgs*) queues;
	Queue* in = args->in;
	Queue* out = args->out;
	char* dequeued;
	char c;

	while(1) {
		dequeued = dequeueString(in);

		if (dequeued != NULL) { // if we don't have the eot
			for (int i = 0; i < BUFFSIZE; i++) {
				c = dequeued[i];
				if (c == '\0') break;
				if (c == ' ') dequeued[i] = '*';
			}
			enqueueString(out, dequeued);
		} else { // we do have the eot
			enqueueString(out, NULL);
			pthread_exit(NULL);
		}
	}
}

void* munch2(void * queues) {
	MunchArgs* args = (MunchArgs*) queues;
	Queue* in = args->in;
	Queue* out = args->out;
	char* dequeued;
	char c;

	while(1) {
		dequeued = dequeueString(in);

		if (dequeued != NULL) { // if we don't have the eot
			for (int i = 0; i < BUFFSIZE; i++) {
				c = dequeued[i];
				if (c == '\0') break;
				if (c >= 'a' && c <= 'z') dequeued[i] = c - 32;
			}
			enqueueString(out, dequeued);
		} else {
			enqueueString(out, NULL);
			pthread_exit(NULL);
		}
	}
}

// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "munch.h"

#define BUFFSIZE buffsize()

/** Convert spaces to asterisks */
void* munch1(void * queues) {
	MunchArgs* args = (MunchArgs*) queues;
	Queue* in = args->in;
	Queue* out = args->out;
	char buffer[BUFFSIZE];
	char* copy = (char*) malloc(BUFFSIZE * sizeof(char));
	char c;
	int endFlag = 0; // whether we should end

	while(!endFlag) {
		char *dequeued = dequeueString(in);

		if (dequeued != NULL) { // if we don't have the eot
			strcpy(buffer, dequeued);
			for (int i = 0; i < BUFFSIZE; i++) {
				c = buffer[i];
				if (c == '\0') break;
				if (c == ' ') buffer[i] = '*';
			}
			strcpy(copy, buffer);
			enqueueString(out, copy);
		} else { // we do have the eot
			endFlag = 1;
			enqueueString(out, NULL);
		}
	}

	return NULL;
}

void* munch2(void * queues) {
	MunchArgs* args = (MunchArgs*) queues;
	Queue* in = args->in;
	Queue* out = args->out;
	char buffer[BUFFSIZE];
	char* copy = (char*) malloc(BUFFSIZE * sizeof(char));
	char c;
	int endFlag = 0; // whether we should end

	while(!endFlag) {
		char *dequeued = dequeueString(in);

		if (dequeued != NULL) { // if we don't have the eot
			strcpy(buffer, dequeued);
			for (int i = 0; i < BUFFSIZE; i++) {
				c = buffer[i];
				if (c == '\0') break;
				if (c >= 'a' && c <= 'z') buffer[i] = c - 32;
			}
			strcpy(copy, buffer);
			enqueueString(out, copy);
		} else {
			endFlag = 1;
			enqueueString(out, NULL);
		}
	}

	return NULL;
}

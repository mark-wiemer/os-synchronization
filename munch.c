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
		strcpy(buffer, dequeueString(in));

		if (strcmp(eot(), buffer)) { // if we don't have the eot
			for (int i = 0; i < BUFFSIZE; i++) {
				c = buffer[i];
				if (c == '\0') break;
				if (c == ' ') buffer[i] = '*';
			}
		} else {
			endFlag = 1;
		}

		strcpy(copy, buffer);
		enqueueString(out, copy);
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
		strcpy(buffer, dequeueString(in));

		if (strcmp(eot(), buffer)) { // if we don't have the eot
			for (int i = 0; i < BUFFSIZE; i++) {
				c = buffer[i];
				if (c == '\0') break;
				if (c >= 'a' && c <= 'z') buffer[i] = c - 32;
			}
		} else {
			endFlag = 1;
		}

		strcpy(copy, buffer);
		enqueueString(out, copy);
	}

	return NULL;
}

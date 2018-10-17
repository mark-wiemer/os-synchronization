// Mark Wiemer mww 9074356420
// Jenny Ye haengjung 9075878315

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "queue.h"

void* read(void* v) {
	Queue* queue = (Queue*) v;
	char* buffer;
	int validLine = 0;
	int lastLine = 0;
	int c;
	while (1) {
		buffer = (char*) malloc(BUFFSIZE * sizeof(char));
		if (buffer == NULL) {
			fprintf(stderr, "ERROR: malloc failed\n");
			return NULL;
		}
		validLine = 0;
		lastLine = 0;
		for (int i=0 ; i < BUFFSIZE ; i++) {
			c = getchar();
			if (c == '\n') {
				buffer[i] = '\0';
				validLine = 1;
				break;
			}
			if (c == EOF) {
				buffer[i] = '\0';
				validLine = 1;
				lastLine = 1;
				break;
			}
			buffer[i] = c;
		}
		if (!validLine){
			fprintf(stderr, "ERROR: line too long, it was discarded\n");
			free(buffer); // this buffer is never enqeued, we must free it now
			//read rest of line or to end of file
			while ((c = getchar()) != '\n' && c != EOF) {
				// printf("Last char: %c\n", c);
			}
			// if EOF, we are done
			if (c == EOF) {
				enqueueString(queue, NULL);
				return NULL;
			}
		} else {
			enqueueString(queue, buffer);
			if (lastLine) {
				enqueueString(queue, NULL);
				return NULL;
			}
		}
	}
}

